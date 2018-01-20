#ifndef DEVNAME
#define DEVNAME "ProChar-DD"
#endif

#ifndef MAJOR_NO
#define MAJOR_NO 0
#endif

#ifndef MINOR_NO
#define MINOR_NO 0
#endif

typedef struct 
{
	struct Qset *next;
	void **data;
}Qset;

//mydev struct
typedef struct
{
	struct Qset *first;
	struct cdev c_dev;
}Dev;

//pointer to struct 
Dev *dev;

//major number, minor number, number of devices
int majorno,minorno, nod;

dev_t devid;

//this will be the api that will be exported into the kernel symbol table and can be used by other kernel modules/driver
int provider_module(void);

int openDev(struct inode*, struct file*);
int releaseDev(struct inode*, struct file*);
ssize_t writeDev(struct file*, const char *, size_t, loff_t *);
ssize_t readDev(struct file *filep,char *user, size_t size, loff_t *lofp);
