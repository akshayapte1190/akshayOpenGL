#include<stdio.h>

int main(int argc, char *argv, char *envp)
{
	int Division(int, int);

	int a, b, result;

	printf("\n\n");

	printf("Enter Integer Value For 'A' :");
	scanf_s("%d", &a);

	printf("\n\n");
	printf("Enter Integer Value for 'B'  :");
	scanf_s("%d", &b);

	result = Division(a, b);

	printf("\n\n");
	printf("Division of %d and %d is %d ", a, b, result);

	return(0);
}

int Division(int num1, int num2)
{
	int div;

	div = num1 / num2;

	return div;
}

