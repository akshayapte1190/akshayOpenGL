#include<stdio.h>
#include<conio.h>

void main(void)
{
	int num1;
	printf("Enter Number to check Even or Odd :");
	scanf("%d", &num1);

	if (num1 % 2 == 0)
		printf("%d is even number", num1);
	else
		printf("%d is odd number", num1);
}