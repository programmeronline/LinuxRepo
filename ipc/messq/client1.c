#include "declarations.h"
#define CLI_RES_FIFO_NAME "cli_%d"

//#define DEBUG
COMMAND cmnd;
MESS_RES clientres;
MESS_COMMAND mess;
int main()
{
	int msgid,ret;
	if((msgid = msgget( (key_t)1234, 0666|IPC_CREAT)) == -1)
	{
		perror("Client 1 msgget:");
		exit(0);
	}
	mess.msg_cmnd_type = 1;
/*
	sprintf(cmnd.mess_cmnd, "`%c%d;%d;%d",'+',12,34,getpid());

	printf("Client 1 pid = %d Message prepared, type %ld mess %s\n",getpid(),cmnd.msg_cmnd_type,cmnd.mess_cmnd);
*/
	cmnd.op = '+';
	cmnd.op1 = 12;
	cmnd.op2 = 34;
	cmnd.pid = getpid();
	mess.cmnd = cmnd;
	if( msgsnd(msgid, (void *)&mess, sizeof(MESS_COMMAND),0) == -1 )
	{
		perror("Client 1 msgsnd command:");
	}
	if( msgrcv( msgid,(void *)&clientres,sizeof(clientres),(long int)getpid(),0 )==-1 )
	{
		perror("Client 1 msgrcv result:");
	}
	printf("Client 1 pid = %d result of %d %c %d =  %d \n",getpid(),mess.cmnd.op1,mess.cmnd.op, mess.cmnd.op2,clientres.res.result);
	exit(0);
}
