#include "declarations.h"
#define CLI_RES_FIFO_NAME "cli_%d"

//#define DEBUG
COMMAND cmnd;
MESS_RES clientres;
MESS_COMMAND mess;

static int sem_res_wait();
static int sem_res_wait();
static int sem_res_release();

int sersemid;
int main()
{
	int msgid,ret;
	srand(getpid());
	sersemid = semget((key_t)SEMA_KEY, 2 , 0666|IPC_CREAT);
	if(sersemid == -1)
		perror("client1 semget:");

	if((msgid = msgget( (key_t)MESQ_KEY, 0666|IPC_CREAT)) == -1)
	{
		perror("Client 1 msgget:");
		exit(0);
	}
	mess.msg_cmnd_type = COMMAND_MESS_TYPE;
/*
	sprintf(cmnd.mess_cmnd, "`%c%d;%d;%d",'+',12,34,getpid());

	printf("Client 1 pid = %d Message prepared, type %ld mess %s\n",getpid(),cmnd.msg_cmnd_type,cmnd.mess_cmnd);
*/
	cmnd.op = '+';
	cmnd.op1 = rand()%100;
	cmnd.op2 = rand()%100;
	cmnd.pid = getpid();
	mess.cmnd = cmnd;
	if(!sem_ser_wait())
	{
		if( msgsnd(msgid, (void *)&mess, sizeof(MESS_COMMAND),0) == -1 )
		{
			perror("Client 1 msgsnd command:");
		}
		sem_ser_release();

		if( msgrcv( msgid,(void *)&clientres,sizeof(clientres),(long int)getpid(),0 )==-1 )
		{
			perror("Client 1 msgrcv result:");
		}
		printf("Client 1 pid = %d result of %d %c %d =  %d \n",getpid(),mess.cmnd.op1,mess.cmnd.op, mess.cmnd.op2,clientres.res.result);
	}


	exit(0);
}

int sem_ser_wait()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	//printf("Before wait\n");
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		printf("after wait inside\n");
		return 1;
	}
	//printf("wait getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	//printf("after wait\n");
	//perror("Client wait ser :");
	return 0;
}

int sem_ser_release()
{

	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	//printf("release getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	//printf("release getval %d\n",semctl(sersemid, SER_CMND_SEMA , GETVAL, 0));
	return 1;
}
