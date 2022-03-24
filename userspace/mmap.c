#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int fd, file_size;
	int i = 0;
	char *data, *new_pointer,*my_text = "I am at 4096 ";
	fd = open("/home/ehswar/linux/mmap/file", O_RDWR);
	printf("Page size is %u\n",getpagesize());
	if(fd > -1)
	{
		file_size = lseek(fd, 0, SEEK_END);
		data = (char *)malloc(sizeof(char));
		printf("Requested address is %x\n",(unsigned int)data);
		new_pointer =  (char *)mmap(data,file_size, PROT_WRITE,MAP_SHARED, fd, 4096);
		perror("mmap:");
		printf("Allocated address is %x\n",(unsigned int)new_pointer);
		printf("Data mapped is :%s\n",new_pointer);
		while(1)
		{
			memcpy(new_pointer, my_text, strlen(my_text));
			perror("MEMCPY: ");
			*(new_pointer+strlen(my_text)) = i+48;
			sleep(1);
			i++;
		}
		printf("Data mapped is :%s\n",new_pointer);
	}
	else
		perror("Open failed: ");
	return 0;
}
