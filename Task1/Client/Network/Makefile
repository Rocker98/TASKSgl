ifeq ($(OS),Windows_NT)
	client: main.o reConnect.o inputUserFromClient.o
		gcc -I../Client/Netwrk main.o reConnect.o inputUserFromClient.o -o client -lpthread -ladvapi32 -lws2_32

	VPATH += ../Client/libs
	VPATH += ../volodymyr_petuniak/Platform
	main.o : main.c Client.h platform.h
		gcc -I../Platform -c -I../Client/Network main.c  

	reConnect.o : reConnect.c Client.h platform.h
		gcc -c reConnect.c 

	inputUserFromClient.o : inputUserFromClient.c Client.h platform.h
		gcc -c inputUserFromClient.c 

	clean:
		rm *.o client.exe
endif
ifeq ($(detected_OS),Linux)
    client: main.o reConnect.o inputUserFromClient.o
		gcc -I../Client/Netwrk main.o reConnect.o inputUserFromClient.o -o client -lpthread

	VPATH += ../Client/libs
	VPATH += ../volodymyr_petuniak/Platform
	main.o : main.c Client.h platform.h
		gcc -I../Platform -c -I../Client/Network main.c  

	reConnect.o : reConnect.c Client.h platform.h
		gcc -c reConnect.c 

	inputUserFromClient.o : inputUserFromClient.c Client.h platform.h
		gcc -c inputUserFromClient.c 

	clean:
		rm *.o client.exe
endif