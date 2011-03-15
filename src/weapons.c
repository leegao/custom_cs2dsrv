/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "weapons.h"

void AddWeapon(short id, char name[], short wpndmg, short wpndmg_z1,
		short wpndmg_z2, short freq, short speed, short slot, short price,
		short range, short accuracy, short ammo1, short ammo2, int reloadtime,
		short special, short team)
{
	if (name != NULL)
	{
		weapons[id].name = malloc(strlen(name) + 1);
		if (weapons[id].name == NULL)
			error_exit("Memory Error in AddWeapon()\n");
		strncpy(weapons[id].name, name, strlen(name) + 1);
	}
	else
	{
		weapons[id].name = NULL;
	}
	weapons[id].weapondamage = wpndmg;
	weapons[id].weapondamage_z1 = wpndmg_z1;
	weapons[id].weapondamage_z2 = wpndmg_z2;
	weapons[id].freq = freq;
	weapons[id].speed = speed;
	weapons[id].slot = slot;
	weapons[id].price = price;
	weapons[id].range = range;
	weapons[id].accuracy = accuracy;
	weapons[id].ammo1 = ammo1;
	weapons[id].ammo2 = ammo2;
	weapons[id].reloadtime = reloadtime;
	weapons[id].special = special;
	weapons[id].team = team;
}
void WeaponInit()
{
	int i;
	for (i = 0; i <= 0xff; i++){
		AddWeapon(i, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3); //3 to make unbuyable by default
	}
	/*
	 * id, name, wpndmg, wpndmg_z1, wpndmg_z2, freq, speed, slot, price, range, accuracy, ammo1, ammo2, reloadtime, special, team
	 *
	 * str = ""
	 * fmt = "AddWeapon(%s, "%s", %s, %s, %s, %s, 1, %s, %s, %s, %s, %s, %s, %s, %s, 0);\n"
	 * wtype = {'name', 'dmg', 'dmz_z1', 'dmg_z2', 'rate', 'slot', 'price', 'range', 'dispersion', 'ammo', 'ammoin', 'reload', 'recoil'}
	 *
	 * function map(f, list)
	 *     r = {}
	 *     for i,v in ipairs(list) do
	 *         r[i] = f(v)
	 *     end
	 *     return r
	 * end
	 *
	 * for i=1,0xff do
	 *     str = str .. fmt:format(i, unpack(map(function(t) return itemtype(i, t) end, wtype)))
	 * end
	 * */

	//weapons table
	AddWeapon(1, "USP", 24, 0, 0, 360, 1, 2, 500, 300, 0, 12, 100, 1100, 1, 0);
	AddWeapon(2, "Glock", 21, 0, 0, 360, 1, 2, 400, 250, 0, 20, 120, 1100, 2, 0);
	AddWeapon(3, "Deagle", 34, 0, 0, 600, 1, 2, 650, 300, 0, 7, 35, 1050, 0, 0);
	AddWeapon(4, "P228", 22, 0, 0, 360, 1, 2, 600, 300, 0, 13, 53, 1350, 0, 0);
	AddWeapon(5, "Elite", 22, 0, 0, 320, 1, 2, 1000, 300, 0, 15, 120, 1250, 0, 0);
	AddWeapon(6, "Five-Seven", 21, 0, 0, 280, 1, 2, 750, 300, 0, 20, 100, 2400, 0, 0);
	AddWeapon(10, "M3", 26, 0, 0, 800, 1, 1, 1700, 50, 10, 8, 32, 2250, 6, 0);
	AddWeapon(11, "XM1014", 22, 0, 0, 480, 1, 1, 3000, 50, 10, 7, 32, 1750, 6, 0);
	AddWeapon(20, "MP5", 13, 0, 0, 120, 1, 1, 1500, 300, 2, 30, 120, 1150, 0, 0);
	AddWeapon(21, "TMP", 9, 0, 0, 80, 1, 1, 1250, 100, 4, 30, 120, 1000, 0, 2);
	AddWeapon(22, "P90", 11, 0, 0, 80, 1, 1, 2350, 300, 3, 50, 100, 1750, 0, 0);
	AddWeapon(23, "Mac 10", 9, 0, 0, 80, 1, 1, 1400, 100, 4, 30, 90, 1700, 0, 1);
	AddWeapon(24, "UMP45", 15, 0, 0, 160, 1, 1, 1700, 300, 3, 25, 90, 1750, 0, 0);
	AddWeapon(30, "AK-47", 22, 0, 0, 120, 1, 1, 2500, 300, 3, 30, 90, 1375, 0, 1);
	AddWeapon(31, "SG552", 24, 35, 0, 160, 1, 1, 3500, 325, 0, 30, 90, 1250, 4, 1);
	AddWeapon(32, "M4A1", 22, 0, 0, 120, 1, 1, 3100, 300, 2, 30, 90, 1100, 1, 2);
	AddWeapon(33, "Aug", 24, 35, 0, 160, 1, 1, 3500, 325, 0, 30, 90, 2100, 4, 2);
	AddWeapon(34, "Scout", 45, 50, 100, 800, 1, 1, 2750, 350, 0, 10, 60, 900, 5, 0);
	AddWeapon(35, "AWP", 50, 65, 150, 2600, 1, 1, 4750, 400, 0, 10, 30, 2000, 5, 0);
	AddWeapon(36, "G3SG1", 32, 37, 45, 240, 1, 1, 5000, 350, 1, 20, 60, 2300, 5, 0);
	AddWeapon(37, "SG550", 30, 35, 40, 240, 1, 1, 4200, 350, 1, 30, 90, 2250, 5, 0);
	AddWeapon(38, "Galil", 13, 0, 0, 120, 1, 1, 2000, 300, 1, 35, 90, 1250, 0, 1);
	AddWeapon(39, "Famas", 14, 0, 0, 120, 1, 1, 2250, 300, 1, 25, 90, 1250, 2, 2);
	AddWeapon(40, "M249", 15, 0, 0, 80, 1, 1, 5750, 300, 8, 100, 200, 2300, 0, 0);
	AddWeapon(41, "Tactical Shield", 0, 0, 0, 0, 1, 1, 1000, 0, 0, 0, 0, 0, 0, 2);
	AddWeapon(45, "Laser", 1000, 0, 0, 1200, 1, 1, 6500, 1000, 0, 15, 45, 1000, 0, 3);
	AddWeapon(46, "Flamethrower", 30, 0, 0, 120, 1, 1, 3200, 55, 0, 100, 200, 1000, 0, 3);
	AddWeapon(47, "RPG Launcher", 325, 0, 0, 2000, 1, 1, 4000, 700, 0, 1, 2, 2500, 0, 3);
	AddWeapon(48, "Rocket Launcher", 70, 0, 0, 800, 1, 1, 5500, 700, 0, 20, 60, 1500, 0, 3);
	AddWeapon(49, "Grenade Launcher", 75, 0, 0, 800, 1, 1, 5500, 320, 0, 20, 60, 1500, 0, 3);
	AddWeapon(50, "Knife", 45, 90, 0, 320, 1, 3, 0, 7, 0, -1, -1, 0, 3, 0);
	AddWeapon(51, "HE", 105, 0, 0, 400, 1, 4, 300, 320, 0, 1, 0, 0, 7, 0);
	AddWeapon(52, "Flashbang", 0, 0, 0, 400, 1, 4, 200, 320, 0, 2, 0, 0, 7, 0);
	AddWeapon(53, "Smoke Grenade", 0, 0, 0, 400, 1, 4, 300, 320, 0, 1, 0, 0, 7, 0);
	AddWeapon(54, "Flare", 0, 0, 0, 400, 1, 4, 150, 320, 0, 1, 0, 0, 7, 0);
	AddWeapon(55, "Bomb", 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 3);
	AddWeapon(56, "Defuse Kit", 0, 0, 0, 0, 1, 0, 200, 0, 0, 0, 0, 0, 0, 2);
	AddWeapon(57, "Kevlar", 0, 0, 0, 0, 1, 0, 650, 0, 0, 0, 0, 0, 0, 0);
	AddWeapon(58, "Kevlar+Helm", 0, 0, 0, 0, 1, 0, 1000, 0, 0, 0, 0, 0, 0, 0);
	AddWeapon(59, "Night Vision", 0, 0, 0, 0, 1, 0, 1250, 0, 0, 0, 0, 0, 0, 0);
	AddWeapon(61, "Primary Ammo", 0, 0, 0, 0, 1, 0, 50, 0, 0, 0, 0, 0, 0, 0);
	AddWeapon(62, "Secondary Ammo", 0, 0, 0, 0, 1, 0, 50, 0, 0, 0, 0, 0, 0, 0);
	AddWeapon(63, "Planted Bomb", 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3);

}

