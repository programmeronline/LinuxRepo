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
	unsigned int count = 0xFFfff, i = 0;
	sleep(2);
	while( i < count)
	{
		printf("I am a thread with priority %d\n",*(int *)x);
		i++;
	}
	printf("I am done %d\n",*(int *)x);	
}

int main()
{
	struct sched_param sch_param;
	int ret = -1;
	pthread_t pthd;
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
	pthread_join(pthd,NULL);
	exit(0);
	return 0;
}
