/*
 * Published under GPLv3.
 * For more information take a look at the Readme
 * Copyright (c) by the authors of this file
 *
 * Author/s of this file: Jermuk
 */

#include "map.h"

/**
 * \fn void ReadMap()
 * \brief reads the map and put all needed information into a variable
 * needed: tspawn and ctspawn
 */
void ReadMap()
{
	FILE *file;
	int i;
	tspawncount = 0;
	ctspawncount = 0;

	const char* header = "Unreal Software's Counter-Strike 2D Map File";
	const char* maxheader = "Unreal Software's Counter-Strike 2D Map File (max)";
	//const char* check = "ed.erawtfoslaernu";

	char *mappath = malloc(u_strlen(sv_map) + 5);
	memcpy(mappath, sv_map, u_strlen(sv_map));
	memcpy(mappath + u_strlen(sv_map), ".map", 5);

	file = fopen(mappath, "rb");
	if (file == NULL)
		error_exit("Map not found.. Abort\n");
		else
		printf("Loading '%s'..", mappath);

	free(mappath);

	//------------------------------
	char *mapheader = (char*)ReadLine(file);
	// Legacy maps have a different paddding - This causes a bug in de_cs2d where parts of the player cannot be shot at.
	if (strcmp(mapheader, header) == 0){ // Legacy maps uses this padding scheme (pre 0104, still usable by 0118)
		for (i = 1; i <= 9; i++)
			ReadByte(file);
		for (i = 1; i <= 10; i++)
			ReadInt(file);
		for (i = 1; i <= 10; i++)
			ReadLine(file);
	} else if (strcmp(mapheader, maxheader) == 0){ // Max maps uses this scheme
		for (i = 1; i <= 10; i++)
			ReadLine(file);
	}
	unsigned char *code = ReadLine(file);
	unsigned char *tileset = ReadLine(file);
	unsigned char loaded = ReadByte(file);
	int maxx = ReadInt(file);
	int maxy = ReadInt(file);
	int max2[] = {maxx, maxy};
	map.tc = max2;
	unsigned char *background = ReadLine(file);
	/*int backgroundx =*/
	ReadInt(file); //avoid warnings: unused variable
	/*int backgroundy =*/
	ReadInt(file);
	/*unsigned char red =*/
	ReadByte(file);
	/*unsigned char green =*/
	ReadByte(file);
	/*unsigned char blue =*/
	ReadByte(file);
	unsigned char *mapcheck = ReadLine(file);
	//-----------------------------------------
	unsigned char *tilemode = malloc(loaded + 1);
	if (tilemode == NULL)
		error_exit("Memory error in ReadMap()\n");
	for (i = 0; i <= loaded; i++)
	{
		tilemode[i] = ReadByte(file);
	}

	map.tiles = malloc(maxx * sizeof(struct TILE *));
	if (map.tiles == NULL)
		error_exit("Memory error in ReadMap()\n");
	for (i = 0; i <= maxx; i++)
	{
		map.tiles[i] = malloc(maxy * sizeof(struct TILE *));
		if (map.tiles[i] == NULL)
			error_exit("Memory error in ReadMap()\n");
		int b;
		for (b = 0; b <= maxy; b++)
		{
			unsigned char bytecache = ReadByte(file);
			if (bytecache > loaded)
			{
				bytecache = 0;
			}
			map.tiles[i][b].tileid = bytecache;
			map.tiles[i][b].mode = tilemode[bytecache];
			//eprintf("%d|%d: %d|%d\n", i, b, map[i][b].tileid, map[i][b].mode);
		}
	}
	//---------------------------------------
	unsigned char entities_count = ReadByte(file);
	map.entities = (struct ENTITY*)malloc(sizeof(struct ENTITY)*entities_count);
	map.ec = entities_count;
	for (i = 0; i <= entities_count - 1; i++){
		map.entities[i].name = (char*)ReadLine(file);
		map.entities[i].type = ReadByte(file);
		int x = map.entities[i].x = ReadInt(file);
		int y = map.entities[i].y = ReadInt(file);
		map.entities[i].trigger = (char*)ReadLine(file);

		int b;
		for (b = 0; b <= 9; b++){
			map.entities[i].args[b].type = ReadInt(file);
			map.entities[i].args[b].value = (char*)ReadLine(file);
		}

		switch (map.entities[i].type){
		case 0:
			tspawnx[tspawncount] = x;
			tspawny[tspawncount] = y;
			tspawncount++;
			break;
		case 1:
			ctspawnx[ctspawncount] = x;
			ctspawny[ctspawncount] = y;
			ctspawncount++;
			break;
		default:
			break;
		}
	}

	fclose(file);

	eprintf("loaded!\n");
	free(mapheader);
	free(code);
	free(tileset);
	free(background);
	free(mapcheck);
}

/**
 * \fn unsigned char *ReadLine(FILE *file)
 * \brief read from a file stream a cs2d line (ends with \r\n; windows end)
 * \param *file the file stream
 * \return a pointer to the read line
 */
unsigned char *ReadLine(FILE *file)
{
	int position = 0;
	char *line = NULL;
	char c;
	while ((c = fgetc(file)) != 13)
	{
		if (c == EOF)
			error_exit("EndOfFile in ReadByte()\n");

		line = realloc(line, position + 1);
		if (line == NULL)
			error_exit("Memory error in ReadLine()\n");

		line[position] = c;

		position++;
	}

	line = realloc(line, position + 1);
	if (line == NULL)
		error_exit("Memory error in ReadLine()\n");
	line[position] = '\0';
	position++;

	fgetc(file); //0x0A

	return (unsigned char*) line;
}

/**
 * \fn unsigned char ReadByte(FILE *file)
 * \brief read from a file stream a byte
 * \param *file the file stream
 * \return the read byte
 */
unsigned char ReadByte(FILE *file)
{
	unsigned char byte = fgetc(file);
	if (byte == EOF)
		error_exit("EndOfFile in ReadByte()\n");
	return byte;
}
/**
 * \fn int ReadInt(FILE *file)
 * \brief read from a file stream a integer
 * \param *file the file stream
 * \return the read integer
 */
int ReadInt(FILE *file)
{
	int byte1 = fgetc(file);
	if (byte1 == EOF)
		error_exit("EndOfFile in ReadInt()\n");

	int byte2 = fgetc(file);
	if (byte2 == EOF)
		error_exit("EndOfFile in ReadInt()\n");

	int byte3 = fgetc(file);
	if (byte3 == EOF)
		error_exit("EndOfFile in ReadInt()\n");

	int byte4 = fgetc(file);
	if (byte4 == EOF)
		error_exit("EndOfFile in ReadInt()\n");

	return (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
}

long long hashxy(int x, int y){
	return x + ((long long)(y)<<32); // lol flood, I hardcoded the test case into hashxy so I was lyk, wtf, why am I getting the same thing over and over again? <_<
}

/*
 * struct ENTITY* find_entity(ent_s s){
	int i; struct ENTITY e;
	switch (s.type){
	case FIND_BY_XY:
		for (i = 0; i < map.ec; i++){
			e = map.entities[i];
			if (hashxy(e.x,e.y)==(*s.v).hashxy) return &map.entities[i];
		}
		break;
	case FIND_BY_NAME:
		for (i = 0; i < map.ec; i++){
			e = map.entities[i];
			if (!strcmp((*s.v).name,e.name)) return &map.entities[i];
		}
	}
	return 0;
}
 * */

struct ENTITY* find_entity(int n, ...){
	int i; struct ENTITY e;
	va_list ap;
	va_start(ap, n);
	int x = va_arg(ap, int);
	int y = va_arg(ap, int);
	switch (n){
	case FIND_BY_XY:
		for (i = 0; i < map.ec; i++){
			e = map.entities[i];
			if (hashxy(e.x,e.y)==hashxy(x,y)) va_end(ap);return &map.entities[i];
		}
		break;
	case FIND_BY_NAME:
		for (i = 0; i < map.ec; i++){
			e = map.entities[i];
			if (!strcmp((char*)x,e.name)) va_end(ap);return &map.entities[i];
		}
	}
	va_end(ap);
	return 0;
}
