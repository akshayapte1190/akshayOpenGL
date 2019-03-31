#include<stdio.h>
#include<conio.h>

void main(void)
{
	int fact,num=0;
		long factorial=1;

	printf("Enter number :");
	scanf("%d", &fact);

	for (int i = 1; i <= fact; ++i)
	{
		factorial = factorial * i;
	}

	printf("Factorial number of %d is %d", fact, factorial);
}