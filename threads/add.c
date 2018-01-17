#include "declarations.h"
#include "add.h"
extern int res_flag;
extern void *res_shm_ptr;
void add(void *arg)
{

	COMMAND *cmd;
	RES res_t;
	cmd = (COMMAND *)arg;

	res_t.res = cmd->op1 + cmd->op2;
	res_t.pid = cmd->pid;

	memcpy( res_shm_ptr, &res_t, sizeof(res_t) );

	res_flag = 1;

	printf("Hi , I am an adder\n");
}
