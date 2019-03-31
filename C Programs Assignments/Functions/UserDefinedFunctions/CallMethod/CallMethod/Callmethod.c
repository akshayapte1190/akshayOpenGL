#include<stdio.h>

int main(int argc, char *argv, char *envp)
{
	void Addition(void);
	int Subtraction(void);
	void Multiplication(int, int);
	int Division(int, int);

	int result_subtraction;
	int a_multiplication, b_multiplication;
	int a_division, b_division, result_divsion;

	Addition();

	printf("\n\n");
	result_subtraction = Subtraction();
	printf("Subtraction Yields Result = %d\n", result_subtraction);

	printf("\n\n");
	printf("Enter Integer Value For 'A' For Multiplication : ");
	scanf_s("%d", &a_multiplication);
	printf("Enter Integer Value For 'B' For Multiplication : ");
	scanf_s("%d", &b_multiplication);

	Multiplication(a_multiplication, b_multiplication);

	printf("\n\n");
	printf("Enter Integer Value For 'A' For Division : ");
	scanf_s("%d", &a_division);

	printf("Enter Integer For 'B' For Division : ");
	scanf_s("%d", &b_division);

	result_divsion = Division(a_division, b_division);

	printf("\n\n");
	printf("Division Of %d and %d Gives = %d (Quotient)\n", a_division, b_division, result_divsion);
	return(0);
}

void Addition(void)
{
	int a, b, sum;
	printf("\n\n");

	printf("Enter Integer Value For 'A' For Addition :");
	scanf_s("%d", &a);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Addition : ");
	scanf_s("%d", &b);

	sum = a + b;
	printf("\n\n");
	printf("Sum Of %d and %d is %d\n\n", a, b, sum);
	
}

int Subtraction(void)
{
	int a, b, subtraction;

	printf("\n\n");
	printf("Enter Integer Value For 'A' For Subtraction : ");
	scanf_s("%d", &a);

	printf("\n\n");

	printf("Enter Value 'B' For Subtraction : ");
	scanf_s("%d", &b);

	subtraction = a - b;
	return(subtraction);
}

void Multiplication(int num1, int num2)
{
	int multiplication;
	printf("\n\n");
	multiplication = num1 * num2;

	printf("\n\n");
	printf("Multiplication Of %d and %d is %d\n", num1, num2, multiplication);
}


int Division(int num1, int num2)
{
	int division_quotient;

	if (num1 > num2)
		division_quotient = num1 / num2;

	else
		division_quotient = num2 / num1;

	return(division_quotient);
}

