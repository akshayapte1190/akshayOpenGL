#include <stdio.h>

int global_count=0;
int main()
{
	void change_count_one(void);
	void change_count_two(void);

	printf("\n");
	printf("Global Count = %d\n",global_count);

	change_count_one();
	change_count_two();
	return(0);
}

void change_count_one(void)
{
		global_count=global_count+9;
		printf("Global Count=%d\n",global_count);
}

void change_count_two()
{
	global_count=global_count+3;
	printf("Global Count = %d\n",global_count);
}


