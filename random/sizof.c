#include <stdio.h>
#define SIZEOF(x) (int)((char *)(&x+1) - (char*)&x)
int main()
{

int a;
float b;
double c;
long long int d;
long int e;
long double f;
char g;
short int h;
printf("Size of int a is %d\n",SIZEOF(a));
printf("Size of float b is %d\n",SIZEOF(b));
printf("Size of double c is %d\n",SIZEOF(b));
printf("Size of long long int d is %d\n",SIZEOF(d));
printf("Size of long int e is %d\n",SIZEOF(e));
printf("Size of long double f is %d\n",SIZEOF(f));
printf("Size of char g is %d\n",SIZEOF(g));
printf("Size of short int h is %d\n",SIZEOF(h));
//printf("Size of long long double is %d\n",SIZEOF(i));
return 0;
}
