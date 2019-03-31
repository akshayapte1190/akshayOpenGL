#include<stdio.h>
#include<conio.h>


void main(void)
{
	int num1, num2, num3,greatest;

	printf("Enter 3 numbers :");
	scanf("%d%d%d", &num1, &num2, &num3);

	if (num1 > num2 && num1>num3)
	{
		printf("%d is greatest nmumber\n", num1);
	}
	else if (num2 > num1 && num2 > num3)
	{
		printf("%d is greatest nmumber\n", num2);
	}
	else
	{
		printf("%d is greatest number\n", num3);
	}



	//using conditional Operator

	greatest = num1 > num2 ? (num1 > num3 ? num1 : num3) : (num2 > num3 ? num2 : num3);
	printf("Using Conditional operator : %d is greatest number", greatest);
}