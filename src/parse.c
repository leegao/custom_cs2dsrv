/*
 * parse.c
 *
 *  Created on: Mar 29, 2011
 *      Author: leegao
 */

#include "parse.h"

/* tokenizer splits the cmd into the args, returns the cmd-type
 *
	int c;char* s;float port;
	char* cmd = tokenize("  banip \"192.168.1.1\" 3.14",&c,"sf",&s,&port);
	printf("cmd: %s, ip:%s, port:%f, consumed:%d\n",cmd, s,port,c);
 *
 * fmt = s i f
 */
char* tokenize(char* text, int* consumed, char* fmt, ...){
	int i,j, quot = 0, nargs = strlen(fmt);
	*consumed = 0;
	char* cmd = NULL;
	va_list args;
	va_start(args, fmt);

	for (i=-1;i<nargs;i++){
		char* buf = NULL;
		if (!*text) {printf("[Parse] Too few arguments.\n");return NULL;}
		while(*text && *text == ' '){
			text++;(*consumed)++;
		}
		if (*text == '"'){
			quot=1;text++;(*consumed)++;
		}
		for(j=0;text[j];j++){
			// unquoted termination condition
			if (!quot && text[j] == ' '){
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j]='\0';
				while(text[j] == ' ') j++;
				text+=j;
				break;
			// quoted termination condition
			} else if (quot && text[j] == '"'){
				buf = (char*)malloc(j+1);
				memcpy(buf, text, j);
				buf[j]='\0';
				text+=j;
				break;
			}
		}
		if(!buf){
			buf = (char*)malloc(j);
			memcpy(buf, text, j);
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
			return NULL;
		}
	}

	va_end(args);
	return cmd;
}
