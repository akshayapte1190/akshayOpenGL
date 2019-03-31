#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int Subtraction(void);

	int result;

	result = Subtraction();

	printf("\n\n");
	printf("Subtraction is : %d\n\n", result);
	return(0);
}

int Subtraction(void)
{
	int a, b ,subtraction;

	printf("Enter Integer Value of 'A' : ");
	scanf_s("%d", &a);

	printf("Enter Integer Value for 'B' :");
	scanf_s("%d", &b);

	subtraction = a - b;

	return subtraction;
}

