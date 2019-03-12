#include "Server.h"
#include <string.h>

void* inputUserFromServer(void* param1)
{
	arg_struct* param=(arg_struct*)param1;
//	char buf[50];
	char* str1="NewPort-<";
	int i;
	while (true)
	{		
		scanf("%s", &param->inputUser);
		//scanf("%s", &buf);
		
		if(pthread_mutex_trylock(&param->m1)==0){
			if (strstr(param->inputUser,str1)!=0)
			{
				int y = 0;
				for (y;; y++)
				{
					if (param->inputUser[y] == '>')
						break;
					else if(y>20)
					{
					 	 pthread_mutex_unlock(&param->m1);
					 	 return NULL;
					}
				}
				char willBeNextPort[50];
				int iter=0;
				for (i = 0; i < y; i++)
				{
					if (param->inputUser[i] == '<')
					{
						i++;
						do {
							willBeNextPort[iter++] = param->inputUser[i];
							i++;
						} while (param->inputUser[i] != '>'&&i<30);
						if(i>=30)
						{
						 	 pthread_mutex_unlock(&param->m1);
						 	 return NULL;
						}
					}
				}
				param->customPort=atoi(willBeNextPort);
			}
			printf("%s\t%d\n", param->inputUser, param->customPort);
			pthread_mutex_unlock(&param->m1);
		}
	}
	return NULL;	
}
