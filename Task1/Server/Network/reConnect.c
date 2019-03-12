#include "Server.h"

int reConnect(int port, void* param1)
{
	ControlForNewPort* param=(ControlForNewPort*)param1;
	char* newPort;
	char buf[MAXCHARACTER];
	int clientPort;
	int currentPort=port;
	printf("Connected to new port %d. Finaly.\n" , port);
	pthread_mutex_lock(&param->mutex1);
	
	#ifdef _WIN32
	//initialize winsock
	WSADATA wsData;
	int wsock;
	wsock =  WSAStartup(MAKEWORD(2,2), &wsData);
	if (wsock != 0) {
		fprintf(stderr, "Can`t initialize wsock\n" );
		return CAN_NOT_START;
	}
	#endif

	//create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		fprintf(stderr, "Can`t create a socket\n");
		return CAN_NOT_CREATE_SOCKET;
	}

	//bind the socket to address
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (struct sockaddr*)&hint, sizeof(hint));


	//listening
	listen(listening, SOMAXCONN);

	//connecting
	struct sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (struct sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((struct sockaddr*)&client, clientSize, host, NI_MAXHOST, \
		service, NI_MAXSERV, 0) == 0) {
		printf("%s connevted on port %s\n",host, service);
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		printf("%s conected on port %d\n",host, ntohs(client.sin_port));
	}

	//close listening socket
	#ifdef _WIN32
	closesocket(listening);
	#elif _linux_
	close(listening;)
	#endif
	pthread_mutex_unlock(&param->mutex1);
	
	//accept and echo

int byteRecieved1;
	while (true)
	{

		ZeroMemory(buf, MAXCHARACTER);
		//wait for client to send data
		byteRecieved1 = recv(clientSocket, buf, MAXCHARACTER, 0);
		clientPort = atoi(buf);
		if(clientPort!=currentPort)
		{	
			printf("%d",&clientPort);	
			param->newPort = clientPort;
			send(clientSocket,buf, byteRecieved1+1, 0);
			break;
		}
		else if (currentPort != param->customPort)
		{
			printf("%d",param->customPort);
			char willBeNextPort[MAXCHARACTER];
			itoa(param->customPort, willBeNextPort, 10);
			int y = 0;
			for (y;; y++)
			{
				if (param->inputUser[y] == '\0')
					break;
			}
			printf("%d",willBeNextPort);
			send(clientSocket, willBeNextPort, y+1, 0);
			param->newPort = param->customPort;
			break;
		}
		else if (clientPort == currentPort)
		{
			send(clientSocket, buf, byteRecieved1 + 1, 0);
		}
	}

	//close the sock
	#ifdef _WIN32
	closesocket(clientSocket);
	#elif _linux_
	close(clientSocket);
	#endif

	//shutdown sock
	#ifdef _WIN32
	WSACleanup();
	#elif _linux_
	shutdown(clientSocket, SHUT_RDWR);
	#endif
	param->customPort = param->newPort;
	
	return CORRECT_CHANGE;
}
