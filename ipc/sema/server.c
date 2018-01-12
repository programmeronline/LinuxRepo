#include "declarations.h"

#define ADD_CMND_FIFO_NAME "./addcmndfifo"
#define ADD_RES_FIFO_NAME "./addresfifo"

static int init_ser_sem();
static int init_res_sem();

static int sem_res_wait();
static int sem_res_release();

static int sem_destroy_ser();

static int sem_read_release();
static int sem_read_wait();

static int sersemid;


int main()
{
	COMMAND cmnd;
	RES res;
	int sercmndfifo,sercmndfd,cliresfifo,ret,cliresfd;
	int i=0;
	if((mkfifo(SER_FIFO_NAME, 0666) == -1))
		perror("Server ser fifo creation:");

	perror("Ser sema creation");
	sersemid = semget((key_t)KEY, 2 , 0666|IPC_CREAT);
	perror("Ser sema creation");
	printf("Semaphores initialized sersemid = %d\n",sersemid);
	if(sersemid < 0)
		perror("Server semget:");

	if(!init_ser_sem())
		perror("Server initsem semctl:");

	if(!init_res_sem())
		perror("Client 1 initsem semctl:");
	//open the serverfifo for client in read mod
	if((sercmndfd = open(SER_FIFO_NAME, O_RDONLY)) == -1)
		perror("Server open ser fifo");

	while(1)
	{
		printf("In while\n");
		if((read(sercmndfd, &cmnd, sizeof(cmnd)) != sizeof(cmnd)))
		{
			continue;
		}
		printf("Server command received %d %c %d %d\n",cmnd.op1, cmnd.op, cmnd.op2,cmnd.pid);
	}

	if(!sem_destroy())
		perror("Server semdestroy semctl:");

	return 0;
}
//create semaphore for server command fifo
static int init_ser_sem()
{
	union semun sem_union;
	sem_union.val = 2;
	if(semctl(sersemid, SER_CMND_SEMA , SETVAL, sem_union) == -1)
	{
		return 0;
	}
	return 1;
}

//create semaphore for client result fifo
static int init_res_sem()
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sersemid, CLI_RES_SEMA , SETVAL, sem_union) == -1)
	{
		return 0;
	}
	return 1;
}

int sem_read_wait()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	return 1;
}

int sem_read_release()
{

	struct sembuf sem_buf;
	sem_buf.sem_num = SER_CMND_SEMA;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	return 1;
}


int sem_res_wait()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = CLI_RES_SEMA;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	return 1;
}

int sem_res_release()
{

	struct sembuf sem_buf;
	sem_buf.sem_num = CLI_RES_SEMA;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	if(semop(sersemid, &sem_buf, 1) == -1)
	{
		return 0;
	}
	return 1;
}

int sem_destroy_ser()
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sersemid, SER_CMND_SEMA , IPC_RMID, sem_union) == -1)
	{
		return 0;
	}
	return 1;
}
