#include<stdio.h>
#include<conio.h>

void main(void)
{
	int num1, num2;

	printf("Enter 2 numbers :");
	scanf("%d%d", &num1, &num2);

	printf("Sum of %d and %d is %d\n\n", num1, num2, num1 + num2);
	printf("Difference between %d and %d is %d\n\n", num1, num2, num1 - num2);
	printf("Product of %d and %d is %d\n\n", num1, num2, num1*num2);

	//hexadecimal Value
	printf("Hexadecimal of %d is %x\n", num1, num1);

	//Octal Value
	printf("Octal value of %d is %o\n", num1, num1);

	//Character 
	printf("Character value of %d is %c\n", num1, num1);
}