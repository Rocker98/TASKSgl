#include "Client.h"

#define START_PORT 7300


ControlForNewPort arguments;

int main(int argc, char *argv[]) {
	
	pthread_t thread1;
	arguments.customPort = START_PORT;
	if(pthread_create(&thread1, NULL, &inputUserFromClient, (void*)&arguments)!=0) {
		fprintf(stderr, "Error creating thread\n");
		return -1;
	}
	int nextPort = reConnect(START_PORT, &arguments);
	while (nextPort == 0) {
		nextPort = reConnect(arguments.newPort, &arguments);
	}
	return 0;
}
