/*
 * lua_env.h
 *
 *  Created on: Mar 21, 2011
 *      Author: leegao
 */

#ifndef LUA_ENV_H_
#define LUA_ENV_H_

#include "settings.h"

void *_G;
struct{const char* name;int i;}* pfields;
int init_lua();
void lua_cleanup(void* l);
int docall2 (void *L, int narg, int nret);


#endif /* LUA_ENV_H_ */
