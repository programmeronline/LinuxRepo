#include "notifyclient.h"
#include <errno.h>
#define CLI_RES_FIFO_NAME "./cli_%d"
#define DEBUG
void notifyClient(RES res)
{
	int cliresfd,ret;
	pid_t clientpid;
	char clififo[20];

	if(ret == -1){perror("Server read res from addresfifo:");}
	clientpid = res.pid;
	//open the cliresfifo in write mode
	sprintf(clififo,CLI_RES_FIFO_NAME,res.pid);
#ifdef DEBUG
	printf("Client fifo name %s\n",clififo);
#endif
	while((cliresfd = open(clififo, O_WRONLY)) == -1);
	if(cliresfd == -1 ){perror("Server: open cliresfifo:");}
	ret = write(cliresfd, &res, sizeof(res));
	close(cliresfd);
	if(ret == -1){perror("Server writing result to client:");}
	//kill the particular process
#ifdef DEBUG
	printf("Server: server wrtitten res to cliresfifo successfully\n");
#endif
	printf("Pid %d\n",clientpid);
	ret = kill(clientpid, 2);
	printf("ret = %d kill error %d\n",ret,errno);
}
