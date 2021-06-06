#include <stdio.h>

int main(void)
{
	int x = 10;
	int y = 7; 
	printf("%d\n", (x & y));
	x >>= 1; 
	printf("%d\n", x);
	
	return 0;
}
