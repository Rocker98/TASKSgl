#include "Server.h"

#define START_PORT 7300

pthread_t thread1;
pthread_t thread2;

ControlForNewPort arguments;

int main(int argc, char *argv[]) {
	arguments.customPort=START_PORT;
	if(pthread_create(&thread1,NULL,&inputUserFromServer,(void*)&arguments)!=0)
	{
		fprintf(stderr, "Error creating thread\n");
	}
	if(pthread_create(&thread2,NULL,&changePortWithoutUser,(void*)&arguments)!=0)
	{
		fprintf(stderr, "Error creating thread\n");
	}
//	printf("\n second check\n");
	if (pthread_mutex_init(&arguments.mutex1, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return -1;
    }
//	printf("\n third check\n");
	int nextPort=reConnect(START_PORT, (void*)&arguments);
	while (nextPort == CORRECT_CHANGE)
	{
		nextPort = reConnect(arguments.newPort, &arguments);
	}
	pthread_mutex_destroy(&arguments.mutex1);
	return 0;
}
