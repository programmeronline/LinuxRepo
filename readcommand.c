#include "declarations.h"
#include "readcommand.h"
#define DEBUG
COMMAND readCommand(int sercmndfd)
{
	COMMAND cmnd;
	int ret;
	//printf("after read offset = %lld\n",(long long int)lseek(sercmndfd,0,SEEK_CUR));	
	while((ret  = read(sercmndfd, &cmnd, sizeof(cmnd))) != sizeof(cmnd))
	//printf("after read offset = %lld\n",(long long int)lseek(sercmndfd,0,SEEK_CUR));	
	//close(sercmndfd);
	//printf("Command structure %d %c %d %d\n",cmnd.op1,cmnd.op,cmnd.op2,cmnd.pid);
	if(ret == -1){perror("Server: read command from client:");}
#ifdef DEBUG
	printf("Server: command from client is %d %c %d\n",cmnd.op1, cmnd.op,cmnd.op2);
#endif
	return cmnd;
}
