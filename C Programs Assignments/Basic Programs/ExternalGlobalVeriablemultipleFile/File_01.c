

#include<stdio.h>

extern int global_count;

void change_count_one(void)
{
	global_count=global_count + 10;
	printf("Global Count  is = %d\n",global_count);
}

