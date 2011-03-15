/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include "main.h"

int OnJoin(int id);
int OnLeave(int id);
int OnSpecmove(int id, int newx, int newy);
int OnServerStart();
int OnExit();
int OnRespawnRequest(int id);
int OnRespawn(int id);
int OnWeaponChangeAttempt(int id, int wpnid);
int OnAdvancedFire(int id, int status);
int OnFire(int id);
int OnHit(int hitter, int victim);
int OnBuyAttempt(int id, int wpnid);
int OnBuy(int id, int wpnid);
int OnKill(int hitter, int victim, int wpnid);
int OnChatMessage(int id, unsigned char *message, int team);
int OnTeamChangeAttempt(int id, unsigned char team, unsigned char skin);
int OnTeamChange(int id, unsigned char team, unsigned char skin);
int OnMoveAttempt(int id, unsigned short x, unsigned short y, int status);
int OnDrop(int id, unsigned char wpnid, unsigned short ammo1,
		unsigned short ammo2, unsigned char unknown1, unsigned char unknown2,
		unsigned char unknown3);
#endif
