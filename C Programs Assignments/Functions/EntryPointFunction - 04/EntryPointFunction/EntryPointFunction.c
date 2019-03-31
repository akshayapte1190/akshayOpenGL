#include<stdio.h>

int main(int argc, char *argv[])
{
	int i;

	printf("\n\n");
	printf("Hello World !!!\n\n");

	printf("Number Of Command Line Arguments = %d\n\n",argc);

	for (i = 0; i < argc; i++)
	{
		printf("Command Line Argument Number %d = %s\n", (i + 1), argv[i]);
	}
	printf("\n\n");
	return (0);
}
