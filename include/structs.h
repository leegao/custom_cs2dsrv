/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk, FloooD
 */

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "main.h"
#define MAX_CLIENTS 32

struct WEAPON
{
	short weapondamage, weapondamage_z1, weapondamage_z2;
	short reloadtime;
	short freq; //every freq ms one shoot
	short speed;
	short slot;
	short price;
	short range;
	short accuracy;
	short ammo1, ammo2;
	char *name;
	short special;
	short team;
};
/*
 * team
 * 0 - everyone can buy it
 * 1 - t-only
 * 2 - ct only
 * 3 - unbuyable
 */

struct PLAYER_WEAPON
{
	short status;
	short ammo1, ammo2;
};
/*
 * special
 * 0 = Normal
 * 1 = Silencer
 * 2 = Burst
 * 3 = Melee
 * 4 = 1xZoom
 * 5 = 2xZoom
 * 6 = Shotgun
 */

struct DROPPED_WEAPON
{
	short id, uid;
	short ammo1, ammo2;
	short x, y;
};
struct DROPPED_WEAPON **dropped_weapons;
extern int dropped_weapons_count;

struct PLAYER
{
	int used;
	unsigned short client_number;
	unsigned short server_number;
	int lastpacket;
	unsigned short joinstatus;

	unsigned char *name;
	unsigned char *spraylogo;
	unsigned char *win;
	unsigned short version;
	unsigned int usgn; // OMFG, why was this a fucking pointer? this is just fucking ridiculous
	unsigned char team;
	unsigned char skin;
	unsigned short deaths;
	short score;
	unsigned short *x, *y;
	unsigned char health, armor;
	unsigned char actualweapon; //id of used weapon
	struct PLAYER_WEAPON wpntable[0xff];
	float rotation; //-180 to +180
	int specposx, specposy;
	unsigned short money;
	unsigned short kills;
	int reloadtimer, reloading;

	short dead;

	int start;
	unsigned short latency;

	int firetimer, zoomtimer;
	int rcon;

	/* Address*/
	unsigned short port;
	struct in_addr ip;
};
struct PLAYER player[MAX_CLIENTS];

struct TILE
{
	unsigned char mode;
	unsigned char tileid;
};
struct ENTITY{
	char* name;
	unsigned char type;
	int x;
	int y;
	char* trigger;
	struct {
		int type; // defaults to 0
		char* value; // defaults to (char*)0 != '/0'
	} args[10];
};

struct ENT_LL{ // singly linked list
	struct ENT_LL *next;
	struct ENTITY *ent; // pointer to a single entity
}ENT_LL;

struct MUTABLE_ENTITY{
	struct ENTITY *entities; // Entity array (not pointer), search success overrides result from head
	struct ENT_LL *head; // pointer to head of LL
};

struct map{
	int* tc;
	struct TILE **tiles; // Immutable once constructed
	int ec;
	struct ENTITY *entities; // switch to mutable_ent when we allow adding of entities (problematic in current CS2D)
} map;

typedef unsigned char byte;

typedef struct stream_{ // Bytestreams only
	byte* mem; // head of everything
	byte* cur; // head of the stream

	int n, size; // number of bytes, quantas, total num of bytes
} stream;

struct{
	byte* (*read) (stream*, int); // postcondition: byte* is a pointer >= top, top is advanced
	int (*write) (stream*, byte*, int); // precondition: byte* must be a valid pointer, top is unchanged
	int (*trim) (stream*, int);
	byte* (*peek) (stream*); // top is unchanged
	int (*seek) (stream*, int); // top is changed

	//int (*push) (stream*, byte*, int); // Pushes onto the front of the stream, top is decreased
	//byte* (*pop) (stream*, int); // Pops from the back of the stream, top is unchanged

	byte (*read_byte) (stream*);
	short (*read_short) (stream*);
	int (*read_int) (stream*);
	float (*read_float) (stream*);
	byte* (*read_str) (stream*);
	byte* (*read_line) (stream*);

	int (*write_byte) (stream*, byte);
	int (*write_short) (stream*, short);
	int (*write_int) (stream*, int);
	int (*write_float) (stream*, float);
	int (*write_str) (stream*, byte*);
	int (*write_line) (stream*, byte*);

	byte* (*read_str2) (stream*);

	int quanta; // atomic size of mem (not the size of the bytes)
} Stream;

#endif // STRUCTS_H_INCLUDED
