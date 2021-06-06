#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc > 2 || argc == 1)
	{
		printf("Must be one argument\n");
		return -1;
	}

	long number = atoi(argv[1]);
	int digits = 0;
	char flag = 0;
	char isnegative = 1;

	if(number < 0)
		isnegative = -1;

	for(int i = 1; flag == 0; i*= 10)
	{
		if( ( (number * isnegative) - ( 10 * i) ) < 0)
		{
			flag = 1;
		}
		digits++;
	}
	
	printf("The number %ld has %d digits\n", number, digits);
	return 0;
}


