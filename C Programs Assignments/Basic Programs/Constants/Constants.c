#include <stdio.h>
#define MY_PI 3.1415926535897932

enum
{
	SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
};

	enum
	{
		JANUARY = 1,
		FEBRUARY,
			MARCH,
			APRIL,
			MAY,
			JUNE,
			JULY,
			AUGUST,
			SEPTEMBER,
			OCTOBER,
			NOVEMBER,
			DECEMBER,
	};

		enum Numbers
		{
			ONE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			SEVEN,
			EIGHT,
			NINE,
			 TEN
		};

	enum boolean
	{
		TRUE = 1,
		FALSE =0,
	};
int main(void)
{
	const double epsilon = 0.000001;

	printf("\n");
	printf("Local Constant Epsilon = %lf\n",epsilon);
	printf("Sunday is DAy Number = %d\n",SUNDAY);
	printf("Monday is day Number = %d\n",TUESDAY);
	printf("Wednesday is day Number = %d\n",WEDNESDAY);
	printf("Thursday is day Number = %d\n",THURSDAY);
	printf("Friday is day Number = %d\n",FRIDAY);
	printf("Saturday is day Number = %d\n",SATURDAY);

	printf("One is Enum Number = %d\n",ONE);
	printf("Two is Enum Number = %d\n",TWO);
	printf("Three is Enum Number = %d \n",THREE);
	printf("Four is Enum Number = %d \n",FOUR);
	printf("Five is Enum Number = %d \n",FIVE);
	printf("Six is Enum Number = %d \n",SIX);
	printf("Seven is Enum Number = %d \n",SEVEN);
	printf("Eight is Enum Number = %d \n",EIGHT);
	printf("Nine is Enum Number = %d \n",NINE);
	printf("Ten is Enum Number = %d \n",TEN);

	printf("Jan is Enum Number = %d \n",JANUARY);
	printf("Feb is Enum Number = %d \n",FEBRUARY);
	printf("March is Enum Number = %d \n",MARCH);
	printf("April is Enum Number = %d \n",APRIL);
	printf("May is Enum Number = %d \n",MAY);
	printf("June is Enum Number = %d \n",JUNE);
	printf("July is Enum Number = %d \n",JULY);
	printf("August is Enum Number = %d \n",AUGUST);
	printf("September is Enum Number = %d \n",SEPTEMBER);
	printf("October is Enum Number = %d \n",OCTOBER);
	printf("November is Enum Number = %d \n",NOVEMBER);
	printf("December is Enum Number = %d \n",DECEMBER);

		printf("Value of TRUE is  = %d \n",TRUE);
		printf("Value of FALSE is  = %d \n",FALSE);

		printf("Value of MY_PI is  = %10lf\n \n",MY_PI);
		printf("Are of Circle Of Radius 2 units is  = %f \n",(MY_PI*2.0f*2.0f));



	return 0;
}
