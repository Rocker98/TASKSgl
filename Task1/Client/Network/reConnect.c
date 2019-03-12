#include "Client.h"

#define LOCAL_HOST "127.0.0.1"
#define MAX_NUMB_FOR_NEW_PORT 7

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
int inet_pton(int af, const char *src, void *dst);


int reConnect(int port, void* param1){
	ControlForNewPort* param = (ControlForNewPort*)param1;
	char ipAddress[] = LOCAL_HOST;
	char buf[MAXCHARACTER];
	char currentPort[MAX_NUMB_FOR_NEW_PORT];
	int serverPort;
	printf("Connected to new port %d. Finaly.\n",port);

	//initialize
	#ifdef _WIN32
	WSADATA wData;
	int wsResult = WSAStartup(MAKEWORD(2, 2), &wData);
	if (wsResult != 0) {
		fprintf(stderr, "Can`t start\n");
		WSACleanup();
		return CAN_NOT_START;
	}
	#endif

	//create sock
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		fprintf(stderr, "Can`t create a client socket\n");
		closesocket(sock);
		WSACleanup();
		return CAN_NOT_CREATE_SOCKET;
	}
                
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET,ipAddress,&hint.sin_addr);

	//connect to server
	int connResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		fprintf(stderr, "Can`t connect to server\n");
		#ifdef _WIN32
		closesocket(sock);
		#elif _linux_
		close(sock);
		#endif
		#ifdef _WIN32
		WSACleanup();
		#elif _linux_
		shutdown(sock, SHUT_RDWR);
		#endif
		return CAN_NOT_CONNECT_TO_SOCKET;
	}

	//recv()/send()
	while(true)	{
		itoa(port, currentPort, 10);
		int y = 0;
		for (y;; y++) {
			if (currentPort[y] == '\0')
				break;
		}
		if (port==param->customPort) {
			int sendResult2 = send(sock, currentPort, y, 0);
		}
		else if (param->customPort!=port) {
			char willBeNextPort[MAXCHARACTER];
			itoa(param->customPort, willBeNextPort, 10);
			int y = 0;
			for (y;; y++) {
				if (currentPort[y] == '\0')
					break;
			}
			int sendResult3 = send(sock, willBeNextPort, y, 0);
			param->newPort = param->customPort;
			break;
		}
		int byteRecieved = recv(sock, buf, MAXCHARACTER, 0);
		serverPort = atoi(buf);
		

		if (serverPort == port)	{
			continue;
		}
		else if(serverPort==param->customPort)	{
			param->newPort = param->customPort;
			break;
		}
		else if (serverPort!=port)	{
			if (serverPort / port == 10)
				serverPort /= 10;
			param->newPort = serverPort;
			break;
		}
	}
	//close
	#ifdef _WIN32
	closesocket(sock);
	#elif _linux_
	close(sock);
	#endif
	#ifdef _WIN32
	WSACleanup();
	#elif _linux_
	shutdown(sock, SHUT_RDWR);
	#endif
	param->customPort = param->newPort;
	return CORRECT_CHANGE;
}


int inet_pton(int af, const char *src, void *dst) {
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) {
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}

