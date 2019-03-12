#include "BonusTask.h"

void* changePortWithoutUser(void* param1)
{
    ControlForNewPort* param=(ControlForNewPort*)param1;
	int i = 1;
	while (true)
	{
		sleep(45);
		if(pthread_mutex_trylock(&param->mutex1)!=EBUSY)
		{
  		    param->customPort = i;
			i += 10;
			pthread_mutex_unlock(&param->mutex1);
		}
		else continue;
	}
	return NULL;
}

