#include <stdio.h>

int main(void)
{
	int a,b,x;

	printf("\n\n");
	printf("Enter A Number : ");
	scanf("%d",&a);

	printf("\n\n");

	printf("Enter B Number : ");
	scanf("%d",&b);

	printf("\n\n");

	x=a;
	a=a+b;
	printf("Addition Of A=%d and B=%d Gives %d\n",x,a,b);

	x=a;
	a=a-b;
	printf("Subtraction Of A=%d and B=%d Gives %d\n",x,a,b);

	x=a;
	a=a*b;
	printf("Multiplication Of A=%d and B=%d Gives %d\n",x,a,b);

	x=a;
	a=a/b;
	printf("Division Of A=%d and B=%d Gives %d\n",x,a,b);

	x=a;
	a=a%b;
	printf("Modules of A=%d and B=%d Gives Remainder %d\n",x,a,b);

	

	return 0;
}
