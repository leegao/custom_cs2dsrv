/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef PAKETS_H_INCLUDED
#define PAKETS_H_INCLUDED

#include "main.h"
//#include ""

int unknown(stream*, int pid);

typedef int (*unknown_handler) (stream*, struct sockaddr_in*);
typedef int (*known_handler) (stream*, int);

int connection_setup_unknown(stream*, struct sockaddr_in *newclient);
int connection_setup_known(stream*, int id);
int ping_ingame(stream*, int id);
int confirmation_unknown(stream*, struct sockaddr_in *newclient);
int confirmation_known(stream*, int id);
int fire(stream*, int id);
int advanced_fire(stream*, int id);
int buy(stream*, int id);
int rotupdate(stream*, int id);
int posupdatewalk(stream*, int id);
int posupdaterun(stream*, int id);
int posrotupdatewalk(stream*, int id);
int posrotupdaterun(stream*, int id);
int respawnrequest(stream*, int id);
int weaponchange(stream*, int id);
int teamchange(stream*, int id);
int ping_serverlist(stream*, struct sockaddr_in *client);
int serverinfo_request(stream*, struct sockaddr_in *client);
int joinroutine_unknown(stream*, struct sockaddr_in *client);
int specpos(stream*, int id);
int chatmessage(stream*, int id);
int joinroutine_known(stream*, int id);
int leave(stream*, int id);
int reload(stream*, int id);
int spray(stream*, int id);
//int UsgnPacket(int packetid, stream*);
int usgn_add(stream* packet, struct sockaddr_in *newclient);
int usgn_update(stream* packet, struct sockaddr_in *newclient);

int drop(stream*, int id);
int rcon_pw(stream*, int id);


// auxiliary functions
#define NULL_STREAM ((stream*)0)
#define EMPTY_STREAM(s) (!((s)->size))
#define CHECK_STREAM(s,b) if (((s)->size) < (b)){ \
	printf("Invalid packet check: %s()", __func__); \
	return 0; \
}\

stream* init_stream(stream*);
void start_stream();


#endif // PAKETS_H_INCLUDED
