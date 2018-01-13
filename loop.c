#include "headers.h"

int main()
{
	int i=0,n;

	printf("Enter n\n");
	scanf("%d",&n);

	for(i=0; i<n; i++)
	{
		printf("Iteration %d\n",i);
		system("./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1 & ./client1");

	}
//	system("killall client1");
	exit(0);
}
