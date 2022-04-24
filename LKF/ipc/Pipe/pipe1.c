#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2];
	int status;

	status = pipe(fd);

	if(status < 0) {
		perror("Pipe Failed:");
		exit(-1);
	}else{
		printf("Pipe creation successfull\n");
	}

	char buff[20]="How\n";

	write(fd[1],buff,strlen(buff));

	char buff1[20];

	read(fd[0],buff1,sizeof(buff1));	

	close(fd[0]);
	close(fd[1]);

	return 0;
}
