#include "headers.h"
#include "declarations.h"
//#include "fileops.h"
//commented
static int __init init_fun(void)
{
	int ret;
	printk(KERN_INFO "Hello im a KO, I am initialized\n");
	majorno = MAJOR_NO;
	minorno = MINOR_NO;
	//majorno = register_chrdev(majorno, DEVNAME, &fops);
	
	ret = alloc_chrdev_region(&devid,minorno, nod,DEVNAME);
	//if(majorno == -1)
	if(ret == -1)
	{
		printk(KERN_ERR "ERROR: Cannot register device\n");
		goto out;
	}
	majorno = MAJOR(devid);
	minorno = MINOR(devid);
	printk(KERN_INFO "I got major number %d\n",majorno);
	printk(KERN_INFO "I got minor number %d\n",minorno);
	provider_module();
	return 0;
out:
	return -1;
}



static void __exit exit_fun(void)
{
	printk(KERN_INFO "Hello i am a KO, I am leaving BYE!\n");
	//unregister_chrdev(majorno, DEVNAME);
	unregister_chrdev_region(devid,nod);
}

module_init(init_fun);
module_exit(exit_fun);
