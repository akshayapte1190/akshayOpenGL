#include<stdio.h>
#include<conio.h>

void main(void)
{
	int num1;
	printf("Enter number :");
	scanf("%d", &num1);

		if (num1 > 0)
			printf("%d is positive number", num1);
		else if (num1 < 0)
			printf("%d is negative number", num1);
		else if (num1 == 0)
			printf("%d is zero",num1);
}