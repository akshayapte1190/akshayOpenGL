#include<stdio.h>

int main(int argc, char *argv, char *envp)
{
	void Multiplication(int, int);


	int a, b;
	printf("\n\n");
	printf("Enter Integer Value For 'A' : ");
	scanf_s("%d", &a);

	printf("Enter Integer Value For 'B' : ");
	scanf_s("%d", &b);

	Multiplication(a, b);
	return(0);
}

void Multiplication(int num1, int num2)
{
	int multi;

	multi = num1 * num2;

	printf("\n\n");
	printf("Multiplication if %d and %d is %d", num1, num2, multi);
}
