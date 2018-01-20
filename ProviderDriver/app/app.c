#include <stdio.h>
#include <fcntl.h>
int main()
{
	char a='Z';
	int fd,ret;

	if( (fd = open("node",O_WRONLY)) == -1)
	{
		perror("Open");
		return 0;
	}

	printf("fd = %d\n",fd);
	if(  (ret = write(fd, &a, sizeof(char))) == -1 )
	{
		perror("Write: ");
		return 0;
	}
	printf("%d bytes writted\n",ret);
	close(fd);
	return 0;
}
