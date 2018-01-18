#include"declarations.h"
int main()
{
	COMMAND cmd;
	srand(getpid());
	RES res;
	FILE *fp;
	int sfd,nsfd,len,lin=0;
	struct sockaddr_in v,v1;
	
	//-----------------SOCKET-------------------------//
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	
	//printf("sfd=%d\n",sfd);
	
	v.sin_family=AF_INET;
	v.sin_port=htons(5004);
	v.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	len=sizeof(v);
	//-----------------CONNECT----------------------//
	cmd.op1 = rand()%100;
	cmd.op2 = rand()%100;
	cmd.op = '+';

	if( connect(sfd,(struct sockaddr *)&v,len) == -1)
	perror("Connect");
	
	while(write(sfd,&cmd,sizeof(COMMAND)) != sizeof(COMMAND));
	while( read(sfd,&res,sizeof(RES)) != sizeof(RES) );
	
	printf("Client %d got result %d %c %d = %d, BYE!\n",getpid(),cmd.op1,cmd.op,cmd.op2,res.result);
	
	return 0;
}
