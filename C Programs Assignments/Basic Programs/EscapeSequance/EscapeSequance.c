#include <stdio.h>

int main(void)
{
	printf("\n");
	printf("Going On To  Next Line......Using \\n Escape Sequance\n\n");
	printf("Demonstarting \t Horizontal \t Tab \t Using \t \\t Escape Sequance !!! \n\n");

	printf("\" This i sa Double Quoted Output\" Done Using \\\"\\\"Escape Sequance\n\n");

	printf("\'This is A Single Quoted Output \" Done Using \\\'\\\" Escape Sequance\n\n");

	printf("BACKSPACE Turned To BACKSPACE \b Using Escape Sequance \\b \n\n");

	printf("\r Demonstarting Carriage Return Using \\r Escape Sequance \n");
	printf("Demonstarting \r Carriage Return Using \\r Escape Squance \n");
	printf("Demonstarting Carriage \r Return Using \\r Escape Sequance \n\n");

	printf("Demonstarting \x41 Using \\xhh Escape Sequnce \n\n");

	printf("Demonstarting \102 Using \\ooo Escape Sequance\n\n");

	return 0;
}

