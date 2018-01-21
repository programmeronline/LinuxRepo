#ifndef DEVNAME
#define DEVNAME "UserChar-DD"
#endif

#ifndef MAJOR_NO
#define MAJOR_NO 0
#endif

#ifndef MINOR_NO
#define MINOR_NO 0
#endif
int majorno,minorno, nod;
dev_t devid;

//prototype of the exporting api
int provider_module(void);
