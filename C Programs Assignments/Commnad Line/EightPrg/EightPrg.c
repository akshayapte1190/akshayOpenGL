#include<stdio.h>
#include<conio.h>

void main(void)
{
	int month,year;
	printf("Enter month between 01 to 12 : ");
	scanf("%d", &month);

	printf("Enter year : ");
		scanf("%d", &year);

		//By using if-else ladder
	if (month == 1)
		printf("31 days\n");
	else if (month == 2)
	{	
		if(year%4==0)
		printf("29 days\n");
		else
			printf("28 days\n");
	}

	else if(month==3)
		printf("31 days\n");
	else if(month==4)
		printf("30 days\n");
	else if (month == 5)
		printf("31 days\n");

	else if (month == 6)
		printf("30 days\n");

	else if (month == 7)
		printf("31 days\n");

	else if (month == 8)
		printf("31 days\n");

	else if (month == 9)
		printf("30 days\n");

	else if (month == 10)
		printf("31 days\n");

	else if (month == 11)
		printf("30 days\n");

	else if (month == 12)
		printf("30 days\n");



	//by using logical operators
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		printf("using Local operator : 31 days\n");
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		printf("using logical operator : 30 days");
	else if (month == 2)
	{
		if (year % 4 == 0)
		{
			printf("using logical operator : 29 days");
		}
		else
			printf("using logical operator : 28 days");
	}


}
