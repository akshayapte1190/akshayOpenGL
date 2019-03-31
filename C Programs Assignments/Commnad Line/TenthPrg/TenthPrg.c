#include<stdio.h>
#include<conio.h>

void main(void)
{
	int num1,num2;
	char sign;
	long result = 0;
	printf("Enter +,-,*,/ : ");
	scanf("%c", &sign);
	printf("Enter 2 numbers : ");
		scanf("%d%d", &num1, &num2);



	if (sign == '+')
		printf("Addition of %d and %d is %d", num1, num1, num1 + num2);
	else if (sign == '-')
		printf("Division of %d and %d is %d", num1, num1, num1 - num2);
	else if (sign == '*')
		printf("Multiplication of %d and %d is %d", num1, num1, num1 * num2);
	else if (sign == '/')
	{
		result = num1 / num2;
		printf("Division of %d and %d is %3.5ld", num1, num1, result);
	}
	else
		printf("Enter correct sign");
}