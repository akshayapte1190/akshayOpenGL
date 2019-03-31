#include <stdio.h>



void change_count_two(void)
{
	extern int global_count;
	global_count=global_count+3;
	printf("Global Count is = %d\n",global_count);
}
