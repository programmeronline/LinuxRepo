#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define PRIORITY 20
#define POLICY SCHED_RR
//compile with -lpthread option
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_cancel(pthread_t thread);
//

void *thread_routine(void *);
void *thread_routine(void *x)
{
	unsigned int count = 0xFfff, i = 0;
	sleep(1);
	while( i < count)
	{
		if(i % 2 == 0)
			printf("I am a thread with priority %d\n",*(int *)x);
		i++;
	}
	printf("I am done %d\n",*(int *)x);	
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
	int priority1 = 90, priority2 = 70, priority3 = 50;
	if (pthread_getschedparam(pthread_self(), &policy, &sch_param) != 0) {
		printf("pthread_getschedparam failed\n");
		exit(0);
	}
	if (policy == SCHED_FIFO) {
		printf("Sched policy=FIFO\n");
	}else if (policy == SCHED_RR) {
		printf("Sched policy=RR\n");
	}else if(policy == SCHED_OTHER){
		printf("Sched Policy=Other\n");
	}else{
		printf("Unknown Scheduling policy\n");
	}
	printf("Scheduling priority=%d\n",sch_param.sched_priority);
	priority1 = sched_get_priority_max(SCHED_OTHER);
	printf("Max priority for other is =%d\n",priority1);
	priority2 = sched_get_priority_max(SCHED_RR);	
	printf("Max priority for Roundrobin is =%d\n",priority2);
	priority3 = sched_get_priority_max(SCHED_FIFO);
	printf("Max priority for FIFO is =%d\n",priority3);
	//thread 1 priority
	sch_param.sched_priority = priority3;

	ret = pthread_attr_init(&attr);
	if(ret != 0)	
		perror("Init attr");

	ret = pthread_attr_setschedpolicy(&attr, SCHED_RR);
	if(ret != 0)	
		perror("set policy");

	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)	
		perror("set priority");

	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)	
		perror("set inherited");

	ret = pthread_create(&pthd, &attr, &thread_routine, &priority3);
	if(ret != 0)	
	{
		printf("Error is %d\n",ret);
		perror("create thread");
	}
	//thread priority 2
	sch_param.sched_priority = priority3 - 10;
	
	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)	
		perror("set priority");
	
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)	
		perror("set inherited");
	int thd2_priority = sch_param.sched_priority;	
	ret = pthread_create(&pthd2, &attr, &thread_routine, &thd2_priority);
	if(ret != 0)	
	{
		printf("Error is %d\n",ret);
		perror("create thread 2");
	}

	
	//thread priority 3
	sch_param.sched_priority = priority3 - 20;
	
	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)	
		perror("set priority");
	
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)	
		perror("set inherited");
	int thd3_priority = sch_param.sched_priority;	
	ret = pthread_create(&pthd3, &attr, &thread_routine, &thd3_priority);
	if(ret != 0)	
	{
		printf("Error is %d\n",ret);
		perror("create thread 3");
	}


	//thread priority 4
	sch_param.sched_priority = priority3 - 30;
	
	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)	
		perror("set priority");
	
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)	
		perror("set inherited");
	int thd4_priority = sch_param.sched_priority;	
	ret = pthread_create(&pthd4, &attr, &thread_routine, &thd4_priority);
	if(ret != 0)	
	{
		printf("Error is %d\n",ret);
		perror("create thread 4");
	}

	//thread priority 5
	sch_param.sched_priority = priority3;
	
	ret = pthread_attr_setschedparam(&attr, &sch_param);
	if(ret != 0)	
		perror("set priority");
	
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if(ret != 0)	
		perror("set inherited");
	int thd5_priority = 5;	
	ret = pthread_create(&pthd5, &attr, &thread_routine2, &thd5_priority);
	if(ret != 0)	
	{
		printf("Error is %d\n",ret);
		perror("create thread 5");
	}

	pthread_join(pthd,NULL);
	pthread_join(pthd,NULL);
	pthread_join(pthd2,NULL);
	pthread_join(pthd3,NULL);
	pthread_join(pthd4,NULL);
	pthread_join(pthd5,NULL);
	exit(0);
	return 0;
}
