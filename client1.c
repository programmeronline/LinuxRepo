#include "declarations.h"
#define CLI_RES_FIFO_NAME "cli_%d"

//#define DEBUG
int cliresfd;
void displayres(int );
COMMAND cmnd;
RES res;
char clififo[20];
char unl[25]={"unlink "};
void displayres(int signal)
{
	int ret;
#ifdef DEBUG 
	printf("Client in signal handler pid %d\n",getpid());	
#endif
	ret = read(cliresfd, &res, sizeof(res));
	printf("Client 1 %d: Res of %d %c %d = %d ret =%d \n",getpid(),cmnd.op1, cmnd.op, cmnd.op2,res.res,ret);	
	strcat(unl,clififo);
	system(unl);
	kill(getpid(),-9);
}

int main()
{
	int sercmndfd,ret;
	//open serverfifo in write mode
	sercmndfd = open(SER_FIFO_NAME, O_WRONLY);
	//perror("client 1 open:");
	if(sercmndfd == -1){perror("Client cannot open server fifo:");}
	if(signal(2,displayres) == SIG_ERR)
	{
	//	perror("Client: setting signal handler:");
	}
	cmnd.op = '+';
	cmnd.op1 = 1;
	cmnd.op2=2;
	cmnd.pid = getpid();

	//write the command data into serverfifo
	ret = write(sercmndfd,&cmnd,sizeof(cmnd));
	close(sercmndfd);
	if(ret != -1)
		close(sercmndfd);
	//create cliresfifo 
	sprintf(clififo,CLI_RES_FIFO_NAME,getpid());
	printf("Client 1: clififo name %s\n",clififo);
#ifdef DEBUG 
	printf("Client 1: clififo name %s\n",clififo);
#endif
	ret = mkfifo(clififo, 0666);
	if(ret == -1){perror("Client result fifo creation:");}
	//open cliresfifo in read mode
#ifdef DEBUG 
	printf("Client 1: waiting before open \n");
#endif
	if((cliresfd = open(clififo,O_RDWR)) == -1)
	perror("Client 1 : cliresfifo open:");
	
#ifdef DEBUG 
	printf("Client 1: before pause \n");
#endif
	pause();
}
