#include "declarations.h"

static int sem_res_wait();
static int sem_res_release();

int sersemid,ressemid;
int main()
{
	COMMAND cmnd;
	int sercmndfd;
	sersemid = semget((key_t)KEY, 2 , 0666|IPC_CREAT);
	perror("client1 semget:");

	if(sersemid < 0)
		perror("Client 1 semget ser semaphore:");

	cmnd.op1 = 1;
	cmnd.op = '+';
	cmnd.op2 = 2;
	cmnd.pid = getpid();
	//open the serverfifo for client in read mod
	printf("Client 1 semid %d\n",sersemid);
	if((sercmndfd = open(SER_FIFO_NAME, O_WRONLY)) == -1)
		perror("Client 1 open ser fifo");

	perror("Client 1 open ser fifo");
	printf("getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	while(1)
	{
		sleep(1);
		if(!sem_ser_wait())
		{
			printf("In critical section client 2\n");
			write(sercmndfd, &cmnd, sizeof(cmnd));
			sem_ser_release();
			perror("client 1 ser release");
		}
	}

	return 0;
}

int sem_ser_wait()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	printf("Before wait\n");
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		printf("after wait inside\n");
		return 1;
	}
	printf("wait getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	printf("after wait\n");
	perror("Client wait ser :");
	return 0;
}

int sem_ser_release()
{

	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	printf("release getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	printf("release getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	return 1;
}
