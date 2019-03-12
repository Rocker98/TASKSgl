ifeq ($(OS),Windows_NT)
	client: main.o reConnect.o userInputFromServer.o BonusTask.o
		gcc main.o reConnect.o userInputFromServer.o BonusTask.o -o client -lpthread -ladvapi32 -lws2_32

	VPATH += ../Server/libs
	VPATH += ../volodymyr_petuniak/Platform
	main.o : main.c Server.h platform.h
		gcc -I../Platform -c -I../Client/Network main.c  

	reConnect.o : reConnect.c Server.h platform.h
		gcc -I../Platform -c reConnect.c 

	userInputFromServer.o : userInputFromServer.c Server.h platform.h
		gcc -I../Platform -c userInputFromServer.c 

	BonusTask.o : main.c Server.h platform.h BonusTask.o
		gcc -I../Platform -c BonusTask.c

	clean:
		rm *.o server.exe
endif
ifeq ($(detected_OS),Linux)
client: main.o reConnect.o userInputFromServer.o BonusTask.o
		gcc main.o reConnect.o userInputFromServer.o BonusTask.o -o client -lpthread -ladvapi32 -lws2_32

	VPATH += ../Server/libs
	VPATH += ../volodymyr_petuniak/Platform
	main.o : main.c Server.h platform.h
		gcc -I../Platform -c -I../Client/Network main.c  

	reConnect.o : reConnect.c Server.h platform.h
		gcc -I../Platform -c reConnect.c 

	userInputFromServer.o : userInputFromServer.c Server.h platform.h
		gcc -I../Platform -c userInputFromServer.c 

	BonusTask.o : main.c Server.h platform.h BonusTask.o
		gcc -I../Platform -c BonusTask.c

	clean:
		rm *.o server.exe
endif