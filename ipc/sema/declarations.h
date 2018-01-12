#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "headers.h"

#define SER_CMND_SEMA	0
#define CLI_RES_SEMA	1

#define SER_FIFO_NAME  "./ser"
#define KEY	1111
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
	pid_t pid;
	int res;
}RES;
#endif
