#include "declarations.h"
#define ADD_CMND_FIFO_NAME "./addcmndfifo"
#define ADD_RES_FIFO_NAME "./addresfifo"
//#define DEBUG
int main()
{
	COMMAND cmnd;
	RES res;
	int addcmndfd,addresfd,ret;

#ifdef DEBUG
	printf("Add: process started\n");
#endif
	//open addcommandfifo in read mode
	addcmndfd = open(ADD_CMND_FIFO_NAME,O_RDONLY);
	if(addcmndfd == -1){perror("Add: addcmnd open:");}

	//get command data and perform operation
	ret = read(addcmndfd,&cmnd, sizeof(cmnd));
	close(addcmndfd);
	if(ret == -1){perror("Add: read command");}
#ifdef DEBUG
	printf("Add: command received from server %d %c %d\n",cmnd.op1, cmnd.op, cmnd.op2);
#endif
	res.res = cmnd.op1 + cmnd.op2;
	res.pid = cmnd.pid;

	//create resfifo 
	ret = mkfifo(ADD_RES_FIFO_NAME,0666);
	if(ret == -1){/*perror("Add: Add result fifo creation:");*/}

	//open addresfifo in write mode
	addresfd = open(ADD_RES_FIFO_NAME, O_WRONLY);
	if(addresfd == -1){perror("Add: addresfifo open:");}

	//write the res into the addresfifo 
	ret = write(addresfd,&res, sizeof(res));
	if(ret == -1){perror("Add: writing to addresfifo: ");}
	close(addresfd);
	exit(0);
}
