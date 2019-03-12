#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "platform.h"


typedef struct
{
	char inputUser[100];
	int customPort;
	pthread_mutex_t m1;
}arg_struct;


int reConnect(int port,void *);
void* inputUserFromClient(void* param);
