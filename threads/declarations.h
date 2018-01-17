#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "headers.h"

#define SER_CMND_SEMA	0
#define CLI_RES_SEMA	1

#define KEY_SEMA_CMD	1111
#define KEY_SHM_CMD	2222
#define KEY_MESQ_RES	3333


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
	pid_t pid;
	int res;
}RES;
#endif
