#include<stdio.h>
#include<conio.h>


void main(void)
{
	int num1, num2,result;
	printf("Enter 2 numbers :");
	scanf("%d%d", &num1, &num2);
	
	if (num2 > 0)
	{
		result=num1 / num2;
		printf("Division of %d and %d is %ld", num1, num2, result);
	}
	else
		printf("Number must be greater than zero");


}