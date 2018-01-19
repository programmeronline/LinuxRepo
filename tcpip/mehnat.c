//server

#include "declarations.h"

void handle_client(void *arg);
void clear(void);

void sigclear(int sig);
int sfd,nsfd;

void clear(void)
{
printf("Exiting process\n");
close(sfd);
close(nsfd);
}

void sigclear(int sig)
{
printf("Exiting process\n");
close(sfd);
close(nsfd);
}

int main()
{
FILE *fp;
pthread_t tid;
int len,ret;
struct sockaddr_in v,v1;
size_t stksize;
pthread_attr_t atr;

char ser_mess[100],client_mess[100];
//if( atexit(clear) == -1)
//perror("Error registering exit function:");

signal(2,sigclear);
//-----------------SOCKET-------------------------//
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd == -1)
{
perror("socket");
return 0;
}
perror("socket");
printf("sfd=%d\n",sfd);

v.sin_family=AF_INET;
v.sin_port=htons(6666);////////////////////////////////////////////////////////////////
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
pthread_attr_init(&atr);
pthread_attr_setstacksize(&atr,(size_t)1024000);
//if(pthread_create( &tid, NULL, (void *)handle_client, (void *)&nsfd))
if(pthread_create( &tid, (const pthread_attr_t *)&atr, (void *)handle_client, (void *)&nsfd))
{

perror("Server ERROR thread creation failed to handle client");
return 0;
}
// it gets the threads stack size and give
// value in stksize variable
//pthread_attr_getstacksize(&atr, &stksize);
//pthread_attr_setstacksize(&atr,1024000);

//printf("Created thread stack size - > %u\n", (unsigned int)stksize);

//pthread_attr_getstacksize(&atr, &stksize);
// print the current threads stack size
//printf("Modified thread stack size - > %u\n", (unsigned int)stksize);
//getchar();
//pthread_join(tid,(void **)&ret);
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

while( write(socket, &res, sizeof(RES)) != sizeof(RES) );

close(socket);
pthread_detach(pthread_self());
pthread_exit(0);
}

//client

#include"declarations.h"
int sfd,nsfd;

void clear(void);

void sigclear(int);

void clear(void)
{
//printf("Exiting process\n");
close(sfd);
close(nsfd);
}

int main()
{
COMMAND cmd;
srand(getpid());
RES res;
FILE *fp;
int len,lin=0;
struct sockaddr_in v,v1;
size_t stksize;
void *tattr;
//tattr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
//pthread_attr_t atr1;
if( atexit(clear) == -1)
perror("Error registering exit function:");

//printf("Before getting statck size\n");
//pthread_attr_getstacksize(&atr, &stksize);
//printf("After getting statck size\n");
//pthread_attr_setstacksize(&atr,2048000);

//-----------------SOCKET-------------------------//
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("socket");
return 0;
}

//printf("sfd=%d\n",sfd);

v.sin_family=AF_INET;
v.sin_port=htons(6666);
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
//ZC12237-WJWT-W3UA
}

//loop.c

#include "declarations.h"

int main()
{
int i=0,n;

printf("Enter n\n");
scanf("%d",&n);

for(i=0; i{
printf("Iteration ....................................................%d\n",i);
system("./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1");

}
// system("killall client1");
exit(0);
}

//declarations.h

#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "header.h"

#define SER_CMND_SEMA 0
#define CLI_RES_SEMA 1

#define KEY_SEMA_CMD 1111
#define KEY_SHM_CMD 2222
#define KEY_SHM_RES 3333
#define KEY_MESQ_RES 4444

union semun
{
int val;
struct semids_ds *buf;
unsigned short *array;
};

typedef struct
{
pid_t pid;
char op;
int op1;
int op2;
}COMMAND;

typedef struct
{
COMMAND command;
int req_flag;
}SHM_COMMAND;

typedef struct
{
int result;
}RES;

typedef struct
{
long int msg_res_type;
RES res;
}MESS_RES;
#endif

//Makefile

all: server client1
client1: client1.o
gcc -o client1 client.c -lpthread
server: server.o
gcc -o server server.o -lpthread
server.o: server.c declarations.h
gcc -c server.c
client1.o: client.c declarations.h
gcc -c client.c
clean:
rm *.o

//headers.h

#include 
#include 
#include 
#include 
#include <sys/types.h>
#include 
#include <sys/socket.h>
#include <netinet/in.h>
#include

#include <arpa/inet.h>
#include
/*#include<>
#include<>
#include<>
#include<>*/
