#include "declarations.h"

//#define DEBUG
SHM_COMMAND shm_cmnd;

static int init_ser_sem();
static int sem_res_wait ();
static int sem_res_wait ();
static int sem_res_release ();

int shmid_cmd;
int mesqid_res;
int sersemid;

int sem_ser_wait();
int sem_ser_release();
void *cmd_shm_ptr;
int main ()
{
	int msgid, ret;
	SHM_COMMAND shm_cmd;
	COMMAND cmnd;
	MESS_RES mess_res;
	srand (getpid ());

	if((sersemid = semget((key_t)KEY_SEMA_CMD ,1, 0666|IPC_CREAT )) == -1)
		perror("Client 1 semget for command:");

	shmid_cmd = shmget ((key_t) KEY_SHM_CMD, 0 ,0);
	if (shmid_cmd == -1)
		perror ("client 1 shmget of command:");

	if( (cmd_shm_ptr = shmat(shmid_cmd, (void *)0, 0)) == (void *)-1 )
		perror("Client 1 shmat command shmat:");

	if ((mesqid_res = msgget ((key_t) KEY_MESQ_RES, 0666 | IPC_CREAT)) == -1)
	{
		perror ("Client 1 msgget:");
		exit (0);
	}
	/*
	   sprintf(cmnd.mess_cmnd, "'%c%d;%d;%d",'+',12,34,getpid());

	   printf("Client 1 pid = %d Message prepared, type %ld mess %s\n",getpid(),cmnd.msg_cmnd_type,cmnd.mess_cmnd);
	 */
	cmnd.op = '+';
	cmnd.op1 = rand () % 100;
	cmnd.op2 = rand () % 100;
	cmnd.pid = getpid ();
	shm_cmd.req_flag = 1;
	shm_cmd.command = cmnd;
	//printf("Client %d sending request %d %d \n",getpid(),cmnd.op1,cmnd.op2);
	//while( ((SHM_COMMAND *)cmd_shm_ptr)->req_flag != 0 );
	while(1)
	{
		if (((SHM_COMMAND *)cmd_shm_ptr)->req_flag == 0 && !sem_ser_wait ())
		{
			//if( ((SHM_COMMAND *)cmd_shm_ptr)->req_flag == 0 )
			{
				//printf("Client %d in critical section of shm command\n",getpid());
				memcpy(cmd_shm_ptr, &shm_cmd , sizeof(shm_cmd));
				sem_ser_release ();
				break;
			}
			//else
			// sem_ser_release ();
		}
	}
	printf("Client %d waiting for result\n",getpid());
	if (msgrcv(mesqid_res, (void *) &mess_res, sizeof (MESS_RES), (long int) getpid (),0) == -1)
	{
		perror ("Client 1 msgrcv result:");
	}

	printf("Got my result %d %c %d = %d, %ld Bye!\n",cmnd.op1, cmnd.op, cmnd.op2, mess_res.res.result,mess_res.msg_res_type);
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
