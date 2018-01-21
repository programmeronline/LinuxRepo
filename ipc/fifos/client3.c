#include "declarations.h"
#define CLI_RES_FIFO_NAME "cli_%d"

//#define DEBUG
int cliresfd;
void displayres(int );
COMMAND cmnd;
RES res;
void displayres(int signal)
{
	int ret;
#ifdef DEBUG 
	printf("Client 3 in signal handler\n");	
#endif
	ret = read(cliresfd, &res, sizeof(res));
	printf("Client 3: Res of %d %c %d = %d\n",cmnd.op1, cmnd.op, cmnd.op2,res.res);	
}

int main()
{
	int sercmndfd,ret;
	char clififo[20];
	char unl[25]={"unlink "};
	//open serverfifo in write mode
	//sleep(3);
	sercmndfd = open(SER_FIFO_NAME, O_WRONLY);
	//perror("client 3 open:");
	if(sercmndfd == -1){perror("Client cannot open server fifo:");}
	if(signal(2,displayres) == SIG_ERR)
	{
	//	perror("Client: setting signal handler:");
	}
	cmnd.op = '*';
	cmnd.op1 = 30;
	cmnd.op2=40;
	cmnd.pid = getpid();

	//write the command data into serverfifo
	ret = write(sercmndfd,&cmnd,sizeof(cmnd));
	close(sercmndfd);
	//create cliresfifo 
	sprintf(clififo,CLI_RES_FIFO_NAME,getpid());
	printf("Client 3: clififo name %s\n",clififo);
#ifdef DEBUG 
	printf("Client 3: clififo name %s\n",clififo);
#endif
	ret = mkfifo(clififo, 0666);
	if(ret == -1){perror("Client result fifo creation:");}
	//open cliresfifo in read mode
#ifdef DEBUG 
	printf("Client 3: waiting before open cli res fifo \n");
#endif
	cliresfd = open(clififo,O_RDWR);
	
#ifdef DEBUG 
	printf("Client 3: before pause \n");
#endif
	pause();
	strcat(unl,clififo);
	system(unl);
	exit(0);
}
