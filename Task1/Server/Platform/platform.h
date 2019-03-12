#ifdef __linux__ 
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif _WIN64
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#elif _WIN32
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

