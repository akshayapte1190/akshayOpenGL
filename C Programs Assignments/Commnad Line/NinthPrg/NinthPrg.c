#include<stdio.h>
#include<conio.h>


void main(void)
{
	int num1,orginalNumber,reverseNumber=0, rem;

	printf("Enter 5 digit number :");
		scanf("%d", &num1);

	orginalNumber = num1;

	while (num1 != 0)
	{
		rem = num1 % 10;
		reverseNumber = reverseNumber * 10 + rem;
		num1 = num1 / 10;
	}

	if (orginalNumber == reverseNumber)
		printf("%d is Pallindrome number", reverseNumber);
	else
		printf("%d is not Pallindrome number", reverseNumber);

}