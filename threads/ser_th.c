#include "declarations.h"
#include "add.h"

//Macros

//Prototypes
void th_routine(void *);
void init(void);
//globals
int shmid_cmnd;
int mesqid_res;
int res_flag;

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

	if( !sem_wait(&semt))
	{
		perror("Thread sem_wait for result shm:");
		return 0;
	}
	return 1;
}

int unlock_tsem()
{

	if( !sem_post(&semt))
	{
		perror("Thread sem_post for result shm:");
		return 0;
	}
	return 1;
}

void th_routine(void *arg)
{
	pthread_t th_add;

	RES res;
	SHM_COMMAND *shm_cmd;
	memcpy( shm_cmd,arg,sizeof(shm_cmd) );

	printf("Main thread ordered me to %s\n",arg);
	printf("I have done my job, bye!\n");
	//get lock on res flag controlling the shared memory containing the result of operation
	//call add operation and wait for it complete the operation and write the result into 
	if( lock_tsem() )
	{
		res_flag = 0;

		if( pthread_create( &th_add, (void *)0, (void *)add, (void *)(&shm_cmd->command )) == -1 )
			perror("Thread pthread_create add routine:");

		while(!res_flag);

		if( msgsnd(mesqid_res, (void *)&res, sizeof(res), 0 ) == -1  )
			perror("Thread msgsnd result to client:");


		unlock_tsem();
	}
	pthread_exit(0);
	//	the shared memory and make the res_flag true so that we can read the result and send 
	//	it back to the client waiting for it.
	//release the lock on res_flag
}

void init(void)
{

	//create shared memory for client to write the request
	if ((shmid_cmnd = shmget((key_t)KEY_SHM_CMD, sizeof(COMMAND), 0666|IPC_CREAT)) == -1)
		perror("Server shared memory creation for command:");

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

	printf("Hello this is server\n");


	while(1)
	{
		memcpy( &shm_command, cmd_shm_ptr, sizeof(shm_command) );
		if( shm_command.req_flag == 1 )
		{
		((SHM_COMMAND *)cmd_shm_ptr)->req_flag = 0;
		if(!(pthread_create(&tid, (void *)0, (void *)th_routine, (void *)&shm_command)))
			perror("Server thread creation for client");
			
		}
		
	}

	sleep(2);

	return 0;
}
