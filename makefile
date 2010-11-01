win32:
	gcc -c src/*.c
	gcc *.o -lws2_32 -obin/server.exe
	rm *.o
	
posix:
	gcc -c src/*.c
	gcc *.o -obin/server
	rm *.o