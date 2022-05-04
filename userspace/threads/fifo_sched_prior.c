
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>

#define PRIORITY 20
//#define POLICY SCHED_RR
#define POLICY SCHED_FIFO

//compile with -lpthread option
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_cancel(pthread_t thread);
//

void print_affinity();
void *thread_routine(void *);
void *thread_routine(void *x)
{
	int ret ;
	unsigned int count = 0x10, i = 0;
	cpu_set_t mask;
	CPU_ZERO(&mask);//clear all means this process can execute on any core
	CPU_SET(2, &mask);//force the kernel to execute on core 0
	printf("Before set affinity executing on CPU %d\n",sched_getcpu());
	//ret = sched_setaffinity(0, sizeof(cpu_set_t), &mask);

	if(ret != 0)
		perror("Set affinity failed");
	
	while( i < count)
	{
		if(i % 5 == 0)
			printf("I am executing on CPU %d\n",sched_getcpu());
		i++;
	}
	printf("I am done %d\n",*(int *)x);	
	printf("After set affinity executing on CPU %d\n",sched_getcpu());
}
void *thread_routine2(void *x)
{
	int ret;
	struct sched_param my_param;
	int policy;
	pthread_attr_t attr;
	
	ret = pthread_attr_init(&attr);
	if(ret != 0)	
		perror("init attr 5");
	
	ret = pthread_getschedparam(pthread_self(), &policy, &my_param);

	my_param.sched_priority = 20;
	
	int new_priority = my_param.sched_priority;
	
	ret = pthread_attr_setschedparam(&attr, &my_param);
	if(ret != 0)	
	{
		perror("set priority 5");
		printf("Error is %d\n",ret);
	}
	unsigned int count = 0xFF, i = 0;
	while( i < count)
	{
		if(i % 2 == 0)
			printf("I am a thread with priority %d\n",new_priority);
		i++;
	}
	printf("I am done with new priority %d\n",new_priority);	
}

int main()
{
	struct sched_param sch_param;
	int ret = -1;
	pthread_t pthd, pthd2, pthd3, pthd4, pthd5;
	pthread_attr_t attr;
	int policy;
	print_affinity();	
	int priority1 = 90, priority2 = 70, priority3 = 50;
	cpu_set_t mask;
	CPU_ZERO(&mask);//clear all means this process can execute on any core
	CPU_SET(3, &mask);//force the kernel to execute on core 0
	printf("Before set affinity executing on CPU %d\n",sched_getcpu());
	ret = sched_setaffinity(0, sizeof(cpu_set_t), &mask);
	if(ret != 0)
		perror("Set affinity failed");
	print_affinity();
	printf("After set affinity executing on CPU %d\n",sched_getcpu());
	ret = pthread_attr_init(&attr);
	if(ret != 0)
		perror("Attr init failed");
	ret = pthread_create(&pthd, &attr, &thread_routine, &priority1);
	if(ret != 0)
		perror("Thread creation failed");
	int i = 0;
	while(i++ < 0xFF)
		printf("I am main thread executing on %d\n",sched_getcpu());
	pthread_join(pthd, NULL);
	exit(0);	
	return 0;
}

void print_affinity()
{
	cpu_set_t mask;
	int ret;
	ret = sched_getaffinity(0, sizeof(cpu_set_t), &mask);//mask is filled with all CPU avaliable
	if(ret != 0)
		perror("get affinity");
	
	long nproc, i;
	nproc = sysconf(_SC_NPROCESSORS_ONLN);
	printf("sched_getaffinity = ");
	for(i = 0; i < nproc; i++)
		printf("CPU: %d ", CPU_ISSET(i, &mask));
	printf("\n");
}
