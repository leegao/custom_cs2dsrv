#include <stdlib.h>
#include <stdio.h>

#include "lua_env.h"

/* Include the Lua API header files. */
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <luaconf.h>

static const char *progname = "[Lua]";


int traceback (lua_State *L) {
  if (!lua_isstring(L, 1))  /* 'message' not a string? */
    return 1;  /* keep it intact */
  lua_getfield(L, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}

static int docall (lua_State *L, int narg, int clear) {
  int status;
  int base = lua_gettop(L) - narg;  /* function index */
  lua_pushcfunction(L, traceback);  /* push traceback function */
  lua_insert(L, base);  /* put it under chunk and args */
  //signal(SIGINT, laction);
  status = lua_pcall(L, narg, (clear ? 0 : LUA_MULTRET), base);
  //signal(SIGINT, SIG_DFL);
  lua_remove(L, base);  /* remove traceback function */
  /* force a complete garbage collection in case of errors */
  if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
  return status;
}

int docall2 (void *L, int narg, int nret) {
  int status;
  int base = lua_gettop(L) - narg;  /* function index */
  lua_pushcfunction(L, traceback);  /* push traceback function */
  lua_insert(L, base);  /* put it under chunk and args */
  //signal(SIGINT, laction);
  status = lua_pcall(L, narg, nret, base);
  //signal(SIGINT, SIG_DFL);
  lua_remove(L, base);  /* remove traceback function */
  /* force a complete garbage collection in case of errors */
  if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
  return status;
}

static void l_message (const char *pname, const char *msg) {
  if (pname) fprintf(stderr, "%s: ", pname);
  fprintf(stderr, "%s\n", msg);
  fflush(stderr);
}

static int report (lua_State *L, int status) {
  if (status && !lua_isnil(L, -1)) {
    const char *msg = lua_tostring(L, -1);
    if (msg == NULL) msg = "(error object is not a string)";
    l_message("[Lua]", msg);
    lua_pop(L, 1);
  }
  return status;
}


static int dofile (lua_State *L, const char *name) {
  int status = luaL_loadfile(L, name) || docall(L, 0, 1);
  return report(L, status);
}

static const char *get_prompt (lua_State *L, int firstline) {
  const char *p;
  lua_getfield(L, LUA_GLOBALSINDEX, firstline ? "_PROMPT" : "_PROMPT2");
  p = lua_tostring(L, -1);
  if (p == NULL) p = (firstline ? "> " : ">>> ");
  lua_pop(L, 1);  /* remove global */
  return p;
}

#define lua_readline(L,b,p)	\
	((void)L, fputs(p, stdout), fflush(stdout),  /* show prompt */ \
	fgets(b, 512, stdin) != NULL)  /* get line */

static int pushline (lua_State *L, int firstline) {
  char buffer[512];
  char *b = buffer;
  size_t l;
  const char *prmt = get_prompt(L, firstline);
  if (lua_readline(L, b, prmt) == 0)
    return 0;  /* no input */
  l = strlen(b);
  if (l > 0 && b[l-1] == '\n')  /* line ends with newline? */
    b[l-1] = '\0';  /* remove it */
  if (firstline && b[0] == '=')  /* first line starts with `=' ? */
    lua_pushfstring(L, "return %s", b+1);  /* change it to `return' */
  else
    lua_pushstring(L, b);
#define lua_freeline(L,b)	{ (void)L; (void)b; }
  lua_freeline(L, b);
#undef lua_freeline
  return 1;
}

static int incomplete (lua_State *L, int status) {
  if (status == LUA_ERRSYNTAX) {
    size_t lmsg;
    const char *msg = lua_tolstring(L, -1, &lmsg);
    const char *tp = msg + lmsg - (sizeof(LUA_QL("<eof>")) - 1);
    if (strstr(msg, LUA_QL("<eof>")) == tp) {
      lua_pop(L, 1);
      return 1;
    }
  }
  return 0;  /* else... */
}

static int loadline (lua_State *L) {
  int status;
  lua_settop(L, 0);
  if (!pushline(L, 1))
    return -1;  /* no input */
  for (;;) {  /* repeat until gets a complete line */
    status = luaL_loadbuffer(L, lua_tostring(L, 1), lua_strlen(L, 1), "=stdin");
    if (!incomplete(L, status)) break;  /* cannot try to add lines? */
    if (!pushline(L, 0))  /* no more input? */
      return -1;
    lua_pushliteral(L, "\n");  /* add a new line... */
    lua_insert(L, -2);  /* ...between the two lines */
    lua_concat(L, 3);  /* join them */
  }
#define lua_saveline(L,idx)	{ (void)L; (void)idx; }
  lua_saveline(L, 1);
#undef lua_saveline
  lua_remove(L, 1);  /* remove line */
  return status;
}

static void dotty (lua_State *L) {
  int status;
  const char *oldprogname = progname;
  progname = NULL;
  while ((status = loadline(L)) != -1) {
    if (status == 0) status = docall(L, 0, 0);
    report(L, status);
    if (status == 0 && lua_gettop(L) > 0) {  /* any result to print? */
      lua_getglobal(L, "print");
      lua_insert(L, 1);
      if (lua_pcall(L, lua_gettop(L)-1, 0, 0) != 0)
        l_message(progname, lua_pushfstring(L,
                               "error calling " LUA_QL("print") " (%s)",
                               lua_tostring(L, -1)));
    }
  }
  lua_settop(L, 0);  /* clear stack */
  fputs("\n", stdout);
  fflush(stdout);
  progname = oldprogname;
}

int msg(lua_State* l){
	int n = lua_gettop(l), i;
	if (n<1){
		lua_pushstring(l, "msg() requires one argument.");
		lua_error(l);
	}
	stream* m = init_stream(NULL);
	for (i=1;i<=n;i++){
		const char* arg = lua_tostring(l, i);
		Stream.write(m, (byte*)arg, strlen(arg));
		Stream.write_byte(m, ' ');
	}
	Stream.write_byte(m, '\0');
	SendMessageToAll((char*)(m->mem),1);

	return 0;
}

int msg2(lua_State* l){
	int n = lua_gettop(l), i;
	if (n<2){
		lua_pushstring(l, "msg2() requires at least 2 arguments.");
		lua_error(l);
	}
	stream* m = init_stream(NULL);
	int id = lua_tonumber(l, 1);
	for (i=2;i<=n;i++){
		const char* arg = lua_tostring(l, i);
		Stream.write(m, (byte*)arg, strlen(arg));
		Stream.write_byte(m, ' ');
	}
	Stream.write_byte(m, '\0');
	SendMessageToPlayer(id, (char*)(m->mem),1);

	return 0;
}

int new_error(lua_State* l){
	if (lua_gettop(l))
		printf("[Lua] Error: %s\n", lua_tostring(l, 1));
	lua_pushnil(l);
	lua_error(l);
	return 0;
}

int l_player(lua_State* l){
	int n = lua_gettop(l);
	if (n<2){
		lua_pushstring(l, "player() requires exactly two arguments");
		lua_error(l);
	}

	int id = lua_tonumber(l, 1);

	const char* type = lua_tostring(l,2);
#define IS(typ) (!strcmp(type, (typ)))
	if IS("exists"){
		lua_pushboolean(l, player[id].name?1:0);
		return 1;
	}

	if (!player[id].name){
		lua_pushfstring(l, "id %d is not a valid player", id);
		lua_error(l);
	}

	if IS("name"){
		lua_pushstring(l, (char*)player[id].name);
	}else if IS("ip"){
		lua_pushstring(l, inet_ntoa(player[id].ip));
	}else if IS("port"){
		lua_pushinteger(l, player[id].port);
	}else if IS("usgn"){
		lua_pushinteger(l, player[id].usgn);
	}else if IS("ping"){
		lua_pushinteger(l, player[id].latency);
	}else if IS("idle"){
		lua_pushboolean(l, (player[id].lastpacket - mtime()) > 10000); // not correct :P
	}else if IS("bot"){
		lua_pushboolean(l, 0); // for now
	}else if IS("team"){
		lua_pushinteger(l, player[id].team);
	}else if IS("look"){
		lua_pushinteger(l, player[id].skin);
	}else if IS("x"){
		lua_pushinteger(l, *player[id].x);
	}else if IS("y"){
		lua_pushinteger(l, *player[id].y);
	}else if IS("rot"){
		lua_pushnumber(l, (double)player[id].rotation);
	}else if IS("tilex"){
		lua_pushinteger(l, 16+(*player[id].x)/32);
	}else if IS("tiley"){
		lua_pushinteger(l, 16+(*player[id].y)/32);
	}else if IS("health"){
		lua_pushinteger(l, player[id].health);
	}else if IS("armor"){
		lua_pushinteger(l, player[id].armor);
	}else if IS("money"){
		lua_pushinteger(l, player[id].money);
	}else if IS("score"){
		lua_pushinteger(l, player[id].score);
	}else if IS("deaths"){
		lua_pushinteger(l, player[id].deaths);
	}else if IS("teamkills"){
		lua_pushinteger(l, 0); // replace later
	}else if IS("hostagekills"){
		lua_pushinteger(l, 0); // replace later
	}else if IS(""){

	}else{
		lua_pushstring(l, "Player argument is invalid");
		lua_error(l);
	}
#undef IS
	return 1;
}

void init_functions(){
	lua_pushcfunction(_G, msg);
	lua_setfield(_G, LUA_GLOBALSINDEX, "msg");

	lua_pushcfunction(_G, msg2);
	lua_setfield(_G, LUA_GLOBALSINDEX, "msg2");

	lua_pushcfunction(_G, new_error);
	lua_setfield(_G, LUA_GLOBALSINDEX, "error");

	lua_pushcfunction(_G, l_player);
		lua_setfield(_G, LUA_GLOBALSINDEX, "player");
}

int init_lua(){
	_G = lua_open();

	lua_gc(_G, LUA_GCSTOP, 0);
	luaL_openlibs(_G);
	lua_gc(_G, LUA_GCRESTART, 0);

	init_hooks();
	init_functions();
	if(lua_strict){
		// break the print pattern
		const char* strict_print = ""
				//"error();"
				"local __oldprint = print\n"
				"function print(txt, ...)\n"
				"	if ... or type(txt) ~= 'string' then error('print() expects a single string argument'); return end\n"
				"	__oldprint(txt)\n"
				"end\n"
				""
				"local __oldmsg = msg\n"
				"function msg(txt, ...)\n"
				"	if ... or type(txt) ~= 'string' then error('msg() expects a single string argument'); return end\n"
				"	__oldmsg(txt)\n"
				"end\n"
				""
				"local __oldmsg2 = msg2\n"
				"function msg2(id, txt, ...)\n"
				"	if ... or type(txt) ~= 'string' then error('msg2() expects 2 arguments'); return end\n"
				"	__oldmsg2(id, txt)\n"
				"end\n"
				"";
		if (luaL_dostring(_G, strict_print));
	}

	int err = luaL_dofile(_G, lua_file ? lua_file : "server.lua");

	if (err){
		printf("[Lua] Cannot open file %s\n", lua_file ? lua_file : "server.lua");
	}

	return 0;
}

void lua_cleanup(void* l){
	lua_close(l);
}
