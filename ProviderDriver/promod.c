#include "headers.h"
#include "declarations.h"

int provider_module(void)
{
	printk(KERN_INFO "%s Begin\n",__func__);
	printk(KERN_INFO "%s end\n",__func__);
	return 0;
}

