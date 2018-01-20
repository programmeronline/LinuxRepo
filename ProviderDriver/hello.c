#include "headers.h"
#include "declarations.h"
#include "fileops.h"
//commented
int provider_module(void)
{
	printk(KERN_INFO "%s Begin\n",__func__);
	printk(KERN_INFO "%s end\n",__func__);
	return 0;
}
EXPORT_SYMBOL(provider_module);//add provider_module function into the kernel symbol table 

int openDev(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "%s: I am open routine\n",__func__);
	return 0;
}

int releaseDev(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "%s: I am release routine\n",__func__);

	return 0;
}

ssize_t writeDev(struct file *filep, const char *user, size_t size, loff_t *lofp)
{
	printk(KERN_INFO "%s: I am in write routine\n",__func__);
	return 0;
}
ssize_t readDev(struct file *filep,char *user, size_t size, loff_t *lofp)
{
	printk(KERN_INFO "%s: I am in read routine\n",__func__);
	return 0;
}
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
		printk(KERN_ERR "ERROR 1: Cannot register device\n");
		goto out;
	}
	majorno = MAJOR(devid);
	minorno = MINOR(devid);
	//printk(KERN_INFO "I got major number %d\n",majorno);
	//printk(KERN_INFO "I got minor number %d\n",minorno);
	dev = kmalloc(sizeof(Dev),GFP_KERNEL);
	if(!dev)
	{	
		printk(KERN_ERR "ERROR 2: Memory allocation failed!");
		goto out;
	}
	cdev_init( &dev->c_dev, &fops );
	dev->c_dev.ops = &fops; //initialize file ops pointer
	ret = cdev_add(&dev->c_dev, devid, 1);
	if(ret == -1)
	{
		printk(KERN_ERR "ERROR 3: Cannot add cdev");
		goto out;
	}
	printk(KERN_INFO "I got major number %d fetched from dev\n",MAJOR(dev->c_dev.dev));
	printk(KERN_INFO "I got minor number %d fectched from dev\n",MINOR(dev->c_dev.dev));
	return 0;
out:
	return -1;
}



static void __exit exit_fun(void)
{
	printk(KERN_INFO "Hello i am a KO, I am leaving BYE!\n");
	//unregister_chrdev(majorno, DEVNAME);
	cdev_del(&dev->c_dev);
	kfree(dev);
	unregister_chrdev_region(devid,nod);
}

module_init(init_fun);
module_exit(exit_fun);
