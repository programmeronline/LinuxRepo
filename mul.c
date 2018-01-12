#include "declarations.h"
#define MUL_CMND_FIFO_NAME "./mulcmndfifo"
#define MUL_RES_FIFO_NAME "./mulresfifo"
//#define DEBUG
int main()
{
	COMMAND cmnd;
	RES res;
	int addcmndfd,addresfd,ret;

#ifdef DEBUG
	printf("Mul: process started\n");
#endif
	//open addcommandfifo in read mode
	addcmndfd = open(MUL_CMND_FIFO_NAME,O_RDONLY);
	if(addcmndfd == -1){perror("Mul: addcmnd open:");}

	//get command data and perform operation
	ret = read(addcmndfd,&cmnd, sizeof(cmnd));
	close(addcmndfd);
	if(ret == -1){perror("Mul: read command");}
#ifdef DEBUG
	printf("Mul: command received from server %d %c %d\n",cmnd.op1, cmnd.op, cmnd.op2);
#endif
	res.res = cmnd.op1 * cmnd.op2;
	res.pid = cmnd.pid;

	//create resfifo 
	ret = mkfifo(MUL_RES_FIFO_NAME,0666);
	if(ret == -1){/*perror("Add: Add result fifo creation:");*/}

	//open addresfifo in write mode
	addresfd = open(MUL_RES_FIFO_NAME, O_WRONLY);
	if(addresfd == -1){perror("Mul: addresfifo open:");}

	//write the res into the addresfifo 
	ret = write(addresfd,&res, sizeof(res));
	if(ret == -1){perror("Mul: writing to addresfifo: ");}
	close(addresfd);
	exit(0);
}
