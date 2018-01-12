#include "declarations.h"
#include "readcommand.h"
#include "notifyclient.h"

#define ADD_CMND_FIFO_NAME "./addcmndfifo"
#define ADD_RES_FIFO_NAME "./addresfifo"

#define SUB_CMND_FIFO_NAME "./subcmndfifo"
#define SUB_RES_FIFO_NAME "./subresfifo"

#define MUL_CMND_FIFO_NAME "./mulcmndfifo"
#define MUL_RES_FIFO_NAME "./mulresfifo"

//#define DEBUG
int main()
{
	COMMAND cmnd;
	RES res;
	int ret,sercmndfd,cliresfd,addcmndfd,addresfd,subcmndfd,subresfd,mulcmndfd,mulresfd;
	//create serverfifo for client
	ret = mkfifo(SER_FIFO_NAME, 0666);
	int i=0;
	//open the serverfifo for client in read mod
	//read the command data from any client: block on read
	if((sercmndfd = open(SER_FIFO_NAME, O_RDONLY)) == -1)
		perror("Server open ser fifo");
	while(1)
	{
		//printf("After while\n");
		cmnd = readCommand(sercmndfd);
		if(cmnd.pid == 0)
			continue;
		//parse data
		switch(cmnd.op)
		{
			//create child process and exec the operation process
			case '+':
				//create the fifo for operation process
				ret = mkfifo(ADD_CMND_FIFO_NAME, 0666);

				ret = fork();
				if(ret == 0)
				{
					ret  = execl("./add","add",NULL);
					perror("Server: execl:");
					return 0;

				}
				if(ret > 0)
				{
					//open the addcommandfifo in write mode and write the command data
					addcmndfd = open(ADD_CMND_FIFO_NAME, O_WRONLY);
					ret = write(addcmndfd, &cmnd, sizeof(cmnd));
					close(addcmndfd);	
#ifdef DEBUG
					printf("Server: waiting for add result\n");
#endif
					//open addresfifo in read mode and block on read
					//sleep(1);//wait for operationt to complete and create resfifo
					while((addresfd = open(ADD_RES_FIFO_NAME, O_RDONLY)) == -1);
					if(addresfd == -1){perror("Server cannot open addresfifo:");}
					//read the result and parse pid
					//sleep(2);//wait for the 
					ret = read(addresfd, &res, sizeof(res));
					ret = close(addresfd);
					notifyClient(res);
				}
				if(ret == -1)
				{
					perror("Server: exec for add:");			
				}
				break;
//subtraction
				case '-':
				//create the fifo for operation process
				ret = mkfifo(SUB_CMND_FIFO_NAME, 0666);

				ret = fork();
				if(ret == 0)
				{
					ret  = execl("./sub","sub",NULL);
					perror("Server: execl:");
					return 0;

				}
				if(ret > 0)
				{
					//open the addcommandfifo in write mode and write the command data
					subcmndfd = open(SUB_CMND_FIFO_NAME, O_WRONLY);
					ret = write(subcmndfd, &cmnd, sizeof(cmnd));
					close(subcmndfd);
#ifdef DEBUG
					printf("Server: waiting for sub result\n");
#endif
					//open addresfifo in read mode and block on read
					//sleep(1);//wait for operationt to complete and create resfifo
					while((subresfd = open(SUB_RES_FIFO_NAME, O_RDONLY)) == -1);
					if(subresfd == -1){perror("Server cannot open subresfifo:");}
					//read the result and parse pid
					//sleep(2);//wait for the 
					ret = read(subresfd, &res, sizeof(res));
					ret = close(subresfd);
					notifyClient(res);	
				}
				if(ret == -1)
				{
					perror("Server: exec for add:");			
				}
				break;
//multiplication
				case '*':
				//create the fifo for operation process
				ret = mkfifo(MUL_CMND_FIFO_NAME, 0666);

				ret = fork();
				if(ret == 0)
				{
					ret  = execl("./mul","mul",NULL);
					perror("Server: execl:");
					return 0;

				}
				if(ret > 0)
				{
					//open the addcommandfifo in write mode and write the command data
					mulcmndfd = open(MUL_CMND_FIFO_NAME, O_WRONLY);
					ret = write(mulcmndfd, &cmnd, sizeof(cmnd));
					close(mulcmndfd);	
#ifdef DEBUG
					printf("Server: waiting for mul result\n");
#endif
					//open addresfifo in read mode and block on read
					//sleep(1);//wait for operationt to complete and create resfifo
					while((mulresfd = open(MUL_RES_FIFO_NAME, O_RDONLY)) == -1);
					if(mulresfd == -1){perror("Server cannot open mulresfifo:");}
					//read the result and parse pid
					//sleep(2);//wait for the 
					ret = read(mulresfd, &res, sizeof(res));
					ret = close(mulresfd);
					notifyClient(res);	
				}
				if(ret == -1)
				{
					perror("Server: exec for add:");			
				}
				break;
		}
	}
return 0;
}
