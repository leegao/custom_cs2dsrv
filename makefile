all:
	gcc -c src/*.c
	gcc *.o -lws2_32 -obin/server.exe
	gcc *.o -lws2_32 --shared -obin/server.pyc
	rm *.o