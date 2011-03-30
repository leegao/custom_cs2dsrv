/*
 * parse.h
 *
 *  Created on: Mar 29, 2011
 *      Author: leegao
 */

#ifndef PARSE_H_
#define PARSE_H_

#include "main.h"

char* tokenize(char* text, int* consumed, char* fmt, ...);

void* parse_t;
void init_parse();

typedef int(*parse_h)(char*,int*);
void parse(char* text);

#endif /* PARSE_H_ */
