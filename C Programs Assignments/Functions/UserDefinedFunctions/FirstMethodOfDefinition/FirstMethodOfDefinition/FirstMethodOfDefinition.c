#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void Addition(void);

	Addition();
	return(0);
}

void Addition(void)
{
	int a, b, sum;

	printf("\n\n");
	printf("Enter Integer Value For 'A'  :");
	scanf_s("%d", &a);

	printf("\n\n");
	printf("Enter Integer Value For 'B' :");
	scanf_s("%d", &b);

	sum = a + b;

	printf("\n\n");
	printf("Sum Of %d and %d = %d", a, b, sum);
}
