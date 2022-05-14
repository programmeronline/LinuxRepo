#include <stdio.h>
/*
BIG ENDINAN
0- 12
1- 34


LITTLE ENDIAN
0-34
1-12
*/
int main()
{

int a = 0x1234;
char *p;
int endianness;
p = (char*)&a;
printf("Actual address is %x\n",p);
printf("First byte at %x is %x\n",p,*p);
printf("Second byte at %x is %x\n",p+1,*(p+1));
if(*(p+1) == 0x34)
	printf("This is big endian \n");
else
	printf("This is little endian\n");
return 0;
}
