#include<stdio.h>

//Get 10 values from array and display it in another function


void DisplayArray(int *);
void main(void)
{
	int arr[10],i;

	printf("Enter 10 number : ");

	for (i = 0; i < 10; i++)
	{
		//get entered data into arr
		scanf_s("%d", &arr[i]);
	}

	//call to display array
	DisplayArray(arr);
}
void DisplayArray(int *arr)
{
	int j = 0;
	printf("\n\n");
	printf("The values which you are entered are below : ");
	for(;j<10;j++)
	{
		printf("%d\n", arr[j]);
	}
}
