#include<stdio.h>

int main(void)
{
	int num1,value;
	printf("Enter integers number : ");
	scanf("%d",&num1);

	value = BinaryNum(num1);

}

int Binay(int num)
{
	int bin;
	if(num==0)
	{
		return bin;
	}
	else
	{
		bin=num%2;
		num = num/2;
		printf("%d",bin);
		Binary(num);
	}
		
}