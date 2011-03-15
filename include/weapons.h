/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED

#include "main.h"
void AddWeapon(short id, char name[], short wpndmg, short wpndmg_z1,
		short wpndmg_z2, short freq, short speed, short slot, short price,
		short range, short accuracy, short ammo1, short ammo2, int reloadtime,
		short special, short team);
void WeaponInit();

struct WEAPON weapons[0x100];

#endif // WEAPONS_H_INCLUDED
