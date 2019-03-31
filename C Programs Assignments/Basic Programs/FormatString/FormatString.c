#include <stdio.h>

int main(void)
{
	printf("\n");
	
	int a =12;
	int *d=&a;
	printf("Integer Decimal Value Of 'A'=%d'\n",a);
	printf("Integer Octal Value of 'A' = %o\n",a);
	printf("Integer Hexadecimal Value Of 'A' (Hexadecimal Letters in Lower Case) = %x\n",a);
	printf("Integer Hexadecimal Value of 'A' in Upper Case is = %X\n",a);

	printf("Integers value of %p is \n",d);

	char ch = 'A';

	printf("Character ch=%c\n",ch);

	char str[]="AkshayApte";
	printf("String str=%s\n\n",str);

	long num = 30121995L;
	printf("Long Integer = %ld\n\n",num);

	unsigned int b = 7;
	printf("Unsigned Integer 'b'=%u\n\n",b);

	float f_num=3012.1990f;
	printf("Floating point Number With Just %%f 'f_num' = %f\n",f_num);
	printf("Floating Point Number With %%4.2f 'f_num' = %4.2f\n",f_num);
	printf("Floating Point Number With %%2.5f 'f_num' = %2.5f\n\n",f_num);

	double d_pi=3.14159265358979323846;

	printf("Doube Precision Floating Point Number Without Exponential = %g\n",d_pi);
	printf("Double Precision Floating Point Number with Exponential (Lower Case) = %e\n",d_pi);
	printf("Double Precision Floating Point NUmber With Exponential (upper Case) = %E\n",d_pi);
	printf("Double Hexadecimal Value of 'd_pi' (Hexadecimal Letters in Lower Case ) = %a\n",d_pi);
	printf("Double Hexadecimal Value of 'd_pi' (Hexadecimal Letters In Uppar Case) = %A\n",d_pi);

	return(0);
}
