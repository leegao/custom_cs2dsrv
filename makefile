all:
	gcc -O3 -lm -lrt -I"include" src/*.c -o bin/custom_cs2dsrv
