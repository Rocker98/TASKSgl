#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "platform.h"

#define MAXCHARACTER 100
#define CORRECT_CHANGE 0
#define CAN_NOT_START -1
#define CAN_NOT_CREATE_SOCKET -2
#define CAN_NOT_CONNECT_TO_SOCKET -3

typedef struct
{
	char inputUser[MAXCHARACTER];
	int customPort;
	pthread_mutex_t mutex1;
	int newPort;
}ControlForNewPort;

int reConnect(int, void*);
void* inputUserFromServer(void*);
void* changePortWithoutUser(void*);



