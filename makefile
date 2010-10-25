win32:
	gcc -c -I"C:\Python26\include" src/*.c
	gcc *.o -lws2_32 -obin/server.exe
	gcc *.o -lws2_32 -L"C:\Python26\libs" -lpython26 --shared -obin/server.pyd
	rm *.o
	
posix:
	gcc -c src/*.c
	gcc *.o -obin/server
	gcc *.o -lpython26 --shared -obin/server.pyd
	rm *.o