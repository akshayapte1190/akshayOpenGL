#include<stdio.h>
#include<conio.h>

void main(void)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}