#include<stdio.h>
#include<conio.h>
int BinaryNum(int);
int bin;
int main(void)
{
	int num1, value;
	printf("Enter integers number : ");
	scanf_s("%d", &num1);

	value=BinaryNum(num1);
	printf("%d", value);
	_getch();
}

int BinaryNum(int num)
{
	
	if (num == 0)
	{
		return bin;
	}
	else
	{
			bin = num % 2;
			bin = bin * 10;
			num = num / 2;

		//printf("%d", bin);

		BinaryNum(num);
	}
	
}