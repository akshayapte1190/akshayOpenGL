//Get 2D array data and Display

#include<stdio.h>


void DisplayTwoDArray(int,int,int (*arr)[4]);

void main(void)
{
	int arr[2][4], i=0, j;

	for (; i < 2; i++)
	{
		for (j=0; j < 4; j++)
		{
			printf("Enter values for [%d][%d] : ",i,j);

			scanf_s("%d", &arr[i][j]);
		}
	}

	DisplayTwoDArray(2,4,arr);

}

void DisplayTwoDArray(int rows,int cols,int (*arr) [4])
{

	int i = 0, j ;

	for (; i < 2; i++)
	{
		for (j=0; j < 4; j++)
		{
			printf("%d  ", arr[i][j]);
			
		}
		printf("\n");
	}

}