# include <stdio.h>
#include <stdlib.h>
//compile with -fsanitize=address
int main()
{

	int* arr;

	arr = (int *) malloc(sizeof(int) * 10);
	printf("pointer value is %u\n",arr);
	arr = realloc(arr, 1);
	printf("pointer value is %u\n",arr);
	arr[0] = 1;
	arr[1] = 1;
	//printf("size of arr is %d\n",sizeof(arr));

	return 0;
}
