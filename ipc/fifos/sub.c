#include "declarations.h"
#define SUB_CMND_FIFO_NAME "./subcmndfifo"
#define SUB_RES_FIFO_NAME "./subresfifo"
//#define DEBUG
int main()
{
	COMMAND cmnd;
	RES res;
	int addcmndfd,addresfd,ret;

#ifdef DEBUG
	printf("Sub: process started\n");
#endif
	//open addcommandfifo in read mode
	addcmndfd = open(SUB_CMND_FIFO_NAME,O_RDONLY);
	if(addcmndfd == -1){perror("Sub: addcmnd open:");}

	//get command data and perform operation
	ret = read(addcmndfd,&cmnd, sizeof(cmnd));
	close(addcmndfd);
	if(ret == -1){perror("Sub: read command");}
#ifdef DEBUG
	printf("Sub: command received from server %d %c %d\n",cmnd.op1, cmnd.op, cmnd.op2);
#endif
	res.res = cmnd.op1 - cmnd.op2;
	res.pid = cmnd.pid;

	//create resfifo 
	ret = mkfifo(SUB_RES_FIFO_NAME,0666);
	if(ret == -1){/*perror("Add: Add result fifo creation:");*/}

	//open addresfifo in write mode
	addresfd = open(SUB_RES_FIFO_NAME, O_WRONLY);
	if(addresfd == -1){perror("Sub: addresfifo open:");}

	//write the res into the addresfifo 
	ret = write(addresfd,&res, sizeof(res));
	if(ret == -1){perror("Sub: writing to addresfifo: ");}
	close(addresfd);
	exit(0);
}
