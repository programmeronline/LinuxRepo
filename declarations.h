#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "headers.h"

#define SER_FIFO_NAME  "./ser"
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
