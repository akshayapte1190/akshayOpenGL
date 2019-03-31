#include <stdio.h>

int main(void)
{
	int a =5;
	void change_count(void);

	printf("\n");
	printf("A = %d\n",a);

	change_count();

	change_count();

	change_count();

	return 0;
}

void change_count(void)
{
	static int local_count=0;
	local_count = local_count + 8;
	printf("Local Count is = %d\n",local_count);
}

