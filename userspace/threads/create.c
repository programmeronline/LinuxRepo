#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//compile with -lpthread option
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_cancel(pthread_t thread);
//
void thread_routine();
void thread_routine()
{
	char max_arr[2048*100];
	printf("Hello i am a thread \n");
}

int main()
{
	int ret = -1;
	pthread_t pthd;
	ret = pthread_create(&pthd, NULL, (void *)&thread_routine, NULL);
	pthread_join(pthd, NULL);
	return 0;
}
