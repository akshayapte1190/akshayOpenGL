#include <stdio.h>

int main(void)
{
	
	int a,b,result;

	printf("\n\n");

	printf("Enter One Integer : ");
	scanf("%d",&a);

	printf("\n\n");

	printf("Enter Another Integers : ");
	scanf("%d",&b);

	printf("\n\n");

	printf("If answer = 0 , it is 'FALSE' . \n");
	printf("If answer = 1, it is 'TRUE'. \n\n");

	result = (a>b);
	printf("(a>b) A = %d Is Greater Than B=%d			\t Answer=%d\n",a,b,result);

	result = (a<b);
	printf("(a<b) A = %d Is Less Than B=%d			\t Answer=%d\n",a,b,result);

	result = (a<=b);
	printf("(a<b) A = %d Is Less Than Or Equal To B=%d			\t Answer=%d\n",a,b,result);

	result = (a>=b);
	printf("(a>b) A = %d Is Greater Than Or Equal To B=%d			\t Answer=%d\n",a,b,result);

	result = (a==b);
	printf("(a>b) A = %d Is  Equal To B=%d			\t Answer=%d\n",a,b,result);

	result = (a!=b);
	printf("(a>b) A = %d Is NOT Equal To B=%d			\t Answer=%d\n",a,b,result);




	return 0;
}
