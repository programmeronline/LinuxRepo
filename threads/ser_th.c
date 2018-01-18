#include "declarations.h"
#include "add.h"

//Macros

//Prototypes
void th_routine(void *);
void init(void);
int sem_ser_wait();
int sem_ser_release();
static int init_ser_sem();

//globals
int shmid_cmnd;
int shmid_res;
int mesqid_res;
int res_flag;
int sersemid;

//thread semaphore
sem_t semt;

// locks the thread semaphore value used on result data shared memory
static int lock_tsem();

//unlocks the thread semphore value used on result dtat shared memory
static int unlock_tsem();

//pointer to the shared memory containing the result of the operation
void * res_shm_ptr;

//pointer to the shared memory containing the client request
void * cmd_shm_ptr;

int lock_tsem()
{

	if(sem_wait(&semt))
	{
		perror("Thread sem_wait for result shm:");
		return 0;
	}
	return 1;
}

int unlock_tsem()
{

	if(sem_post(&semt))
	{
		perror("Thread sem_post for result shm:");
		return 0;
	}
	return 1;
}

void th_routine(void *arg)
{
	pthread_t th_add;
	int *ret;
	MESS_RES mes_res;
	RES res_t;

	SHM_COMMAND shm_cmd;
	//printf("In thread\n");
	memcpy( &shm_cmd,arg,sizeof(shm_cmd) );
	//printf(" %d ",)
	printf("Main thread ordered me to ............. %d \n",((SHM_COMMAND *)arg)->command.pid);

	//get lock on res flag controlling the shared memory containing the result of operation
	//call add operation and wait for it complete the operation and write the result into
	if( lock_tsem() )
	{
		// printf("Thread in critical sections\n");
		res_flag = 0;

		if( pthread_create( &th_add, (void *)0, (void *)add, (void *)(&shm_cmd.command )))
			perror("Error! Thread pthread_create add routine:");

		//while(!res_flag);
		pthread_join(th_add, (void **)&ret);
		mes_res.msg_res_type = shm_cmd.command.pid;
		// printf("Before result copy\n");
		memcpy( &res_t, res_shm_ptr ,sizeof(RES));
		// printf("After result copy\n");
		printf("Thread reading result %d %d\n",res_t.result,shm_cmd.command.pid);
		mes_res.res = res_t;
		if( msgsnd(mesqid_res, (void *)&mes_res, sizeof(MESS_RES), 0 ) == -1 )
			perror("Thread msgsnd result to client:");

		unlock_tsem();
	}
	pthread_exit(0);
}

void init(void)
{

	//create shared memory for client to write the request
	if((sersemid = semget((key_t)KEY_SEMA_CMD ,1, 0666|IPC_CREAT )) == -1)
		perror("Client 1 semget for command:");

	if( !init_ser_sem())
		perror("Client 1 initsem command shm:");

	if ((shmid_cmnd = shmget((key_t)KEY_SHM_CMD, sizeof(COMMAND), 0666|IPC_CREAT)) == -1)
		perror("Server shared memory creation for command:");

	if ((shmid_res = shmget((key_t)KEY_SHM_RES, sizeof(RES), 0666|IPC_CREAT)) == -1)
		perror("Server shared memory creation for add result:");

	if( (cmd_shm_ptr = shmat(shmid_cmnd, (void *)0, 0)) == (void *)-1 )
		perror("Server shmat command shmat:");

	if( (res_shm_ptr = shmat(shmid_res, (void *)0, 0)) == (void *)-1 )
		perror("Server shmat add result shmat:");

	//create thread semaphore for communication between different add requests
	if((sem_init(&semt, 0, 1)) == -1)
		perror("Server sem_init for result flag creation:");

	//get the message queue id for client result writing
	if((mesqid_res = msgget((key_t) KEY_MESQ_RES, 0666|IPC_CREAT)) == -1 )
		perror("Server msgget res:");

}

int main()
{

	SHM_COMMAND shm_command;

	pthread_t tid;

	init();

	((SHM_COMMAND *)cmd_shm_ptr)->req_flag = 0;
	while(1)
	{
		//printf("Request flag =%d\n",request_flag);
		if (((SHM_COMMAND *)cmd_shm_ptr)->req_flag == 1 && !sem_ser_wait ())
		{
			//if( ((SHM_COMMAND *)cmd_shm_ptr)->req_flag == 1 )
			{
				//printf("Client %d in critical section of shm command\n",getpid());
				memcpy( &shm_command, cmd_shm_ptr, sizeof(shm_command) );
				((SHM_COMMAND *)cmd_shm_ptr)->req_flag = 0;
				sem_ser_release ();

				printf("Creating thread for %d\n",shm_command.command.pid);

				if((pthread_create(&tid, (void *)0, (void *)th_routine, (void *)&shm_command)))
					perror("Error! Server thread creation for client");
			}
			//else
			// sem_ser_release ();
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
