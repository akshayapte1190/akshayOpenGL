// FirstPrg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<conio.h>

int main()
{
	system("cls");
	int num1, num2;
	char ch;
	printf("Enter 2 integer number : ");
	scanf_s("%d%c%d", &num1,&ch, &num2);

	if(ch=='+')

	//Sum of Two integers 
	printf("Sum of %d and %d is %d\n", num1, num2, num1 + num2);
	
}

