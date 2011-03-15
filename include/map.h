/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "main.h"

#define FIND_BY_XY 0
#define FIND_BY_NAME 1

void ReadMap();
unsigned char *ReadLine(FILE *file);
unsigned char ReadByte(FILE *file);
int ReadInt(FILE *file);
#define MAX_SPAWNPOINTS 10

unsigned short tspawnx[MAX_SPAWNPOINTS];
unsigned short tspawny[MAX_SPAWNPOINTS];
unsigned short tspawncount;

unsigned short ctspawnx[MAX_SPAWNPOINTS];
unsigned short ctspawny[MAX_SPAWNPOINTS];
unsigned short ctspawncount;

typedef struct point {int x,y;} point;

//typedef struct ent_s{ // Structure for performing searches, deprecated in favor of variadic
//	int type;
//	union{
//		long long hashxy;
//		point xy;
//		char* name;
//	} *v;
//} ent_s;

long long hashxy(int x, int y); // concatenates the two, primitive hash function, no chance for collision
struct ENTITY* find_entity(int, ...); // search function

#endif // MAP_H_INCLUDED
