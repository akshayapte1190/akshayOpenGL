#include<stdio.h>
#include<conio.h>

void push(int);
void pop();
void display();
int top = -1;
int a[5];
int main()
{
	
	int item,num;

	do {
		printf("Please select from below : \n\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. Display\n");
		printf("0. Exit\n");
		


	scanf_s("%d", &item);
	switch (item)
	{
	case 1:
		printf("Enter element to push : ");
		scanf_s("%d", &num);
		push(num);
		break;

	case 2:
		pop();
		break;

	case 3:
		display();
		break;

	case 0:
		exit(0);
		break;

	default:
		printf("Please enter correct value\n\n");
		break;
	}
} while (1);
	return 0;
}

void push(int num)
{
	if (top <5)
	{
		top++;
		a[top] = num;
		printf("%d is pushed into stack\n\n", a[top]);
	}
	else
	{
		printf("stack is full");
	}
}

void pop()
{
	if (top == -1)
		printf("Stack is empty\n\n");
	else
	{
		//a[top] = NULL;
		printf("%d element is poped\n\n", a[top]);
		top--;
	}
}

void display()
{
	if (top == -1)
	{
		printf("Stack is Empty\n\n");

	}
	else
	{
		for (int i = 0; i <= top; i++)
		{


			printf("Elements in Stack are %d\n", a[i]);
		}
	}
}


