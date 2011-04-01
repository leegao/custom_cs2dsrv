/*
 * parse.c
 *
 *  Created on: Mar 29, 2011
 *      Author: leegao
 */

#include "parse.h"



// p_xxx functions starts here.

int p_banip(char* text, int* consumed){
	char* ip; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\1" "si", &ip, &duration);
	if (!check) return 0;

	// banip_cmd(ip, duration);

	return 1;
}

int p_banname(char* text, int* consumed){
	char* name; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\1" "si", &name, &duration);
	if (!check) return 0;

	// banname_cmd(name, duration);

	return 1;
}

int p_bans(char* text, int* consumed){
	 // declarations
	char* check = tokenize(text, consumed, "\0" "");
	if (!check) return 0;

	// bans_cmd();

	return 1;
}

int p_banusgn(char* text, int* consumed){
	int usgn; int duration = -1;  // declarations
	char* check = tokenize(text, consumed, "\1" "ii", &usgn, &duration);
	if (!check) return 0;

	// banusgn_cmd(usgn, duration);

	return 1;
}

int p_changelevel(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\1" "s", &map);
	if (!check) return 0;

	// changelevel_cmd(map);

	return 1;
}

int p_changemap(char* text, int* consumed){
	char* map;  // declarations
	char* check = tokenize(text, consumed, "\1" "s", &map);
	if (!check) return 0;

	// changemap_cmd(map);

	return 1;
}

int p_customkill(char* text, int* consumed){
	int killer; char* weapon; int victim;  // declarations
	char* check = tokenize(text, consumed, "\3" "isi", &killer, &weapon, &victim);
	if (!check) return 0;

	// customkill_cmd(killer, weapon, victim);

	return 1;
}

int p_deathslap(char* text, int* consumed){
	char* player;  // declarations
	char* check = tokenize(text, consumed, "\1" "s", &player);
	if (!check) return 0;

	// deathslap_cmd(player);

	return 1;
}

// p_xxx ends here




/* tokenizer splits the cmd into the args, returns the cmd-type
 *
	int c;char* s;float port;
	char* cmd = tokenize("  banip \"192.168.1.1\" 3.14",&c,"sf",&s,&port);
	printf("cmd: %s, ip:%s, port:%f, consumed:%d\n",cmd, s,port,c);
 *
 * fmt = s i f
 */
char* tokenize(char* text, int* consumed, char* fmt, ...){
	int min = *(fmt++);
	int i,j, quot = 0, nargs = strlen(fmt), term = 0;
	*consumed = 0;
	char* cmd = NULL;
	va_list args;
	va_start(args, fmt);

	for (i=-1;i<nargs;i++){
		char* buf = NULL;
		if ((!*text || term) && i>=min) {
			va_end(args);
			return cmd;
		}else if (!*text || term){
			printf("[Parse] Too few arguments.\n");
			return NULL;
		}

		while(*text && (*text == ' ' || *text == ';')){
			text++;(*consumed)++;
		}
		if (*text == '"'){
			quot=1;text++;(*consumed)++;
		}
		for(j=0;text[j];j++){
			// unquoted termination condition
			if (!quot && (text[j] == ' ' || text[j] == ';' || !text[j])){
				if (text[j] == ';') term = 1;
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j]='\0';
				while(text[j] == ' ' || text[j] == ';') j++;
				text+=j;
				break;
			// quoted termination condition
			} else if (quot && text[j] == '"'){
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j++]='\0';
				text+=j;
				break;
			}
		}
		if(!buf){
			buf = (char*)malloc(j);
			memcpy(buf, text, j);
			buf[j] = '\0';
			text+=j;
		}

		(*consumed)+=j;
		quot=0;
		if(i<0) {cmd=buf;continue;}
		switch(fmt[i]){
		case 's':{
			char** a = va_arg(args, char**);
			*a = buf;
			break;
		}
		case 'i':{
			int* a = va_arg(args, int*);
			sscanf(buf, "%d", a);
			break;
		}
		case 'f':{
			float* a = va_arg(args, float*);
			sscanf(buf, "%f", a);
			break;
		}
		default:
			printf("[Parse] Bad parser format '%c'\n",fmt[i]);
			va_end(args);
			return NULL;
		}

	}

	va_end(args);
	return cmd;
}

void init_parse(){
	parse_t = hashmap_new();
#define add(type) hashmap_put(parse_t, #type, &p_##type);

	add(banip);

#undef add

}

void parse(char* text){
	if (!*text) return;
	int consumed;
	char* type = tokenize(text,&consumed,"\0");
	parse_h handler;
	int err = hashmap_get(parse_t, (char*)type, (void**)(&handler));
	if (err != MAP_OK){
		printf("[Parse] Invalid command '%s'\n",type);
		return parse(text+consumed);
	}

	int status = handler(text,&consumed);
	if (!status){
		// pass
	}
	parse(text+consumed);
}


