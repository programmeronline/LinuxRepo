
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>
//In this program, thread 1 is created and assumed that it runs first, 
//it runs until i != 100, meanwhile thread2 is created and assumed that it is in the 
//fifo queue to run but it cannot run because a high priority task is currently executing and that thread came first
//when i == 100 , first high priority thread goes to sleep, now the next task in fifo queue is thread2, even though it is having low priority, it will execute until it finishes becuase that is how fifo works, in fifo the first task that gets scheduled continues to execute untill it finishes its execution or it goes into sleep.
//why sched_yield didnt allow second thread to start execute?

#define PRIORITY 20
//#define POLICY SCHED_RR
#define POLICY SCHED_FIFO

//
#define POLICY SCHED_FIFO
void print_affinity();
void *thread_routine(void *);
void *thread_routine(void *x)
{
	int ret ;
	unsigned int count = 0xFFF, i = 0;

	if(ret != 0)
		perror("Set affinity failed");
	while( i < count)
	{
		if(i % 5 == 0)
			printf("######### I am thread 1 ########\n");
		i++;
		if(i == 100)
		{
			printf("Thread 1: I am yielding\n");
			sleep(1);
		}
	}
	printf("I am done %d executing on %d\n",*(int *)x,sched_getcpu());	
}
void *thread_routine2(void *x)
{
	int ret ;
	unsigned int count = 0xFFF, i = 0;

	if(ret != 0)
		perror("Set affinity failed");
	
	while( i < count)
	{
		if(i % 5 == 0)
			printf("######### I am thread 2 ########\n");
		i++;
	}
	printf("I am done %d executing on %d\n",*(int *)x,sched_getcpu());	
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
	ret = pthread_attr_getschedparam(&attr, &sch_param);
	if(ret != 0)
		perror("get shced param failed");

	priority1 = sched_get_priority_max(POLICY);//set highest priority
	sch_param.sched_priority = priority1;
	
	ret = pthread_attr_setschedpolicy(&attr, POLICY);
	if(ret != 0)
		perror("Scheduling policy change failed");

	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)
		perror("change priority failed");
	ret = pthread_attr_setinheritsched(&attr, POLICY);
	if(ret != 0)
		perror("disable inherit failed 1");
	
	ret = pthread_create(&pthd, &attr, &thread_routine, &priority1);
	if(ret != 0)
		perror("Thread creation failed 1");
	
	priority1 = priority1 - 10;;//set highest priority
	sch_param.sched_priority = priority2;
	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)
		perror("change priority failed");
	
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)
		perror("disable inherit failed 2");
	
	ret = pthread_attr_setschedpolicy(&attr, POLICY);
	if(ret != 0)
		perror("Policy change failed 2");
	
	ret = pthread_create(&pthd2, &attr, &thread_routine2, &priority2);
	if(ret != 0)
		perror("Thread creation failed 2");
	pthread_join(pthd, NULL);
	pthread_join(pthd2, NULL);
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
