#include "declarations.h"

static int sersemid;

static int init_ser_sem();

//#define DEBUG
int main()
{
	MESS_COMMAND mess;
	COMMAND cmnd;
	MESS_RES clientres;
	RES res_t;
	int ret,msgid,clientpid;
	int i=0,j,op1,op2;
	char *sop1,*sop2;

	sersemid = semget((key_t)SEMA_KEY, 2 , 0666|IPC_CREAT);
	perror("Ser sema creation:");

	if(!init_ser_sem())
	perror("Server initsem semctl:");

	if( (msgid = msgget((key_t)MESQ_KEY, 0666|IPC_CREAT)) == -1)
	{
		perror("Server msgget:");
		exit(0);
	}
	while(1)
	{
		if( msgrcv(msgid, (void *)&mess,sizeof(MESS_COMMAND),(long int )COMMAND_MESS_TYPE,0) ==-1)
		{
			perror("Server msgrcv command:");
		}
		//printf("Message %s \n",cmnd.mess_cmnd);
		printf("Message type = %ld op = %c op1 = %d op2 = %d pid = %d\n",mess.msg_cmnd_type,mess.cmnd.op,
				mess.cmnd.op1,mess.cmnd.op2, mess.cmnd.pid);
		
		switch(mess.cmnd.op)
		{
			case '+':
				res_t.result = mess.cmnd.op1 + mess.cmnd.op2;
				break;
		}
		clientres.msg_res_type = mess.cmnd.pid; 
		clientres.res = res_t;
		if( msgsnd(msgid, (void *)&clientres, sizeof(MESS_RES), 0)  == -1  )
		{
			perror("Server send result msgsnd:");
			exit(0);
		}
	}
	return 0;
}

//create semaphore for server command fifo
static int init_ser_sem()
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sersemid, SER_CMND_SEMA , SETVAL, sem_union) == -1)
	{
		return 0;
	}
	return 1;
}
