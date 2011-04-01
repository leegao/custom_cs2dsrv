all:
	gcc -O3 -lm -lrt -I"include" -I"lua/src" src/*.c -L. -llua -o bin/custom_cs2dsrv
