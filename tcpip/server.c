#include "declarations.h"

void handle_client(void *arg);
int main()
{
	FILE *fp;
	pthread_t tid;
	int sfd,nsfd,len,i,j,lin;
	struct sockaddr_in v,v1;
	char ser_mess[100],client_mess[100];

	//-----------------SOCKET-------------------------//
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
	printf("sfd=%d\n",sfd);

	v.sin_family=AF_INET;
	v.sin_port=htons(5004);
	v.sin_addr.s_addr=inet_addr("0.0.0.0");
	len=sizeof(v);
	//------------------BIND---------------------------//
	if( bind(sfd,(struct sockaddr *)&v,len) == -1)
		perror("Bind");

	//------------------LISTEN-------------------------//
	if( listen(sfd,100000) == -1)
		perror("listen");
	//------------------ACCEPT-------------------------//
	while(nsfd=accept(sfd,(struct sockaddr *)&v,&len))
	{
		if(nsfd == -1)
		{
			perror("Accept new connection:");
			return 0;
		}
		if(pthread_create( &tid, NULL, (void *)handle_client, (void *)&nsfd))
		{
			
			perror("Server ERROR thread creation failed to handle client");
			return 0;
		}
	}
	close(sfd);
	close(nsfd);
	return 0;
	//write(sfd,a,strlen(a)+1);
}

void handle_client(void *arg)
{

	int socket = *(int *)arg;

	COMMAND cmd;
	RES res;
	
	printf("Handler assigned\n");

	while( read(socket, &cmd, sizeof(COMMAND)) != sizeof(COMMAND));
	
	res.result = cmd.op1 + cmd.op2;
	
	printf("Received request from %d \n",cmd.pid);
	
	while(  write(socket, &res, sizeof(RES)) != sizeof(RES) );
	
	close(socket);
	pthread_exit(0);
}
