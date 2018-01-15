#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "headers.h"
#define MESS_SIZE	(sizeof(int)*2) + sizeof(char)+2
#define RES_SIZE	(sizeof(long int))
typedef struct 
{
char op;
int op1;
int op2;
pid_t pid;
}COMMAND;

typedef struct 
{
	long int msg_cmnd_type;
	COMMAND cmnd;//opop1;op2;pid
}MESS_COMMAND;

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
