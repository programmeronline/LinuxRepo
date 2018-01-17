#include "declarations.h"

//#define DEBUG
SHM_COMMAND shm_cmnd;

static int sem_res_wait ();
static int sem_res_wait ();
static int sem_res_release ();

int shmid_cmd;
int mesqid_res;
int sersemid;

int sem_ser_wait();
int sem_ser_release();
 
int main ()
{
	int msgid, ret;
	COMMAND cmnd;
	RES res;
	srand (getpid ());

	if((sersemid = semget((key_t)KEY_SEMA_CMD ,2, 0666|IPC_CREAT )) == -1)
		perror("Client 1 semget for command:");
	shmid_cmd = shmget ((key_t) KEY_SHM_CMD, sizeof(SHM_COMMAND), 0666 | IPC_CREAT);
	if (shmid_cmd == -1)
		perror ("client 1 shmget of command:");

	if ((mesqid_res = msgget ((key_t) KEY_MESQ_RES, 0666 | IPC_CREAT)) == -1)
	{
		perror ("Client 1 msgget:");
		exit (0);
	}
	/*
	   sprintf(cmnd.mess_cmnd, "`%c%d;%d;%d",'+',12,34,getpid());

	   printf("Client 1 pid = %d Message prepared, type %ld mess %s\n",getpid(),cmnd.msg_cmnd_type,cmnd.mess_cmnd);
	   */
	cmnd.op = '+';
	cmnd.op1 = rand () % 100;
	cmnd.op2 = rand () % 100;
	cmnd.pid = getpid ();

	if (!sem_ser_wait ())
	{
		perror ("Client 1 msgsnd command:");
		sem_ser_release ();

	}

	if (msgrcv(mesqid_res, (void *) &res, sizeof (res), (long int) getpid (),0) == -1)
	{
		perror ("Client 1 msgrcv result:");
	}

	return 0;
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
