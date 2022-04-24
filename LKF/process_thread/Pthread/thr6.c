#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

void* func1(void* args)
{
	printf("Sleeping in %d\n",pthread_self());
	while(1);
	//sleep(6);
	printf("Thread wokeup\n");
	return NULL;
}

void* func2(void* args)
{
	printf("Waiting for 3 seonds and cancelling thread\n");
	sleep(3);
	pthread_cancel((pthread_t)args);
	//pthread_join((pthread_t)args,NULL);
	printf("Killed\n");
	return NULL;
}

int main()
{
	pthread_t tid1,tid2;
	printf("Creating thread\n");
	pthread_create(&tid1,NULL,&func1,NULL);
	pthread_create(&tid2,NULL,&func2,(void*)tid1);
	printf("Created Thread\n");
//	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	while(1);
	return 0;
}
