/* ***** Summary *****
 * This program takes in a decimal number as input and outputs a scaled seven-segmented display
 * The scale can be adjusted by an optional parameter during the program call
 *
 * ***** CHANGELOG *****
 * 1.0: Base program complete
 * 1.1: Removed commented code, fixed spacing, added summary.
 * 1.2: Fixed more spacing and return values. 0 is only returned with successful program execution now; all failures return -1 
 * 1.3: Fixed all formatting. Removed unneeded if conditions 
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_LENGTH 60
#define TRUE 1
#define FALSE 0

// Declared Functions 
unsigned int toDecimal(int base, char *number); // define used functions
int digitValue(char digit, int base);
int power (int base, int exp);
void OutputTopZones (char *number);
void OutputMidZones (char *number);
void OutputBottomZones (char *number);
void grabTopZoneCharacter (char num, char * start, char * mid, char * end);
void grabMidLevelChars (char num, char * start, char * mid, char * end);
void grabBottomLevelChars (char num, char * start, char * mid, char * end);

int signBit = FALSE; // boolean used to indicate wheather or not the input number is negative
int scale = 1; // scale the the numbers will be printed to

int main(int argc, char *argv[])
{
	if ((argc == 1 || argc > 3))
  	{
  		printf("You need to run the program with at least one argument\n");
  		printf("Usage: %s <$number> <$optional_scale>\n", argv[0]);
  		printf("Example: %s 420\n", argv[0]);
  		printf("Type \"%s help\" for more information about the program\n", argv[0]);
    		return -1;
  	}
  
  	char num[NUMBER_LENGTH]; 
  	strcpy(num, argv[1]); // Stores first argument into string
  	if (num[0] == '-') signBit = TRUE; // Test if input number is negative
  	if (num[0] == '+') signBit = FALSE; // Test if input number is postive

  	if (argc == 3) 
  	{
  		scale = -1 * toDecimal(10, argv[2]); // initialize scale to argv[2]
  	}

	if (scale < 1 || scale > 5)
	{
    		printf("Scale must be 1-5\n");
    		return -1; 
  	}

	unsigned int index = 0;

	if (signBit == 1)
  	{ 

    		if (num[1] == 0)
    		{
    			printf("Wrong digit value\n");
    			return -1;
    		}

	index++;
  	}

	while (num[index] != 0)
  	{ 
  		if (! (num[index] > 47 && num[index] < 58))
   		{
    			printf("Only numbers allowed\n");
   			return -1;
    		}
  	
	index++;
  	} 

	OutputTopZones(num); 		// print top zone
	OutputMidZones(num); 		// print mid zone
	OutputBottomZones(num); 	// print bottom zone
	putchar('\n');			// Print new line character
	return 0;
}

// Prints top zones of all numbers 
void OutputTopZones (char *number)
{
	unsigned int i = 0;

	char start;
	char mid;
	char end;

	if (signBit == TRUE)
  	{
 		int lengthOffset = 2 * scale;
    		for (; i < lengthOffset; i++) printf(" ");
    		putchar(' ');
  	}

	if (signBit == TRUE)
	{
		i = 1;
  	} else {
    		i = 0;
  	}

	while (number[i])
	{
    		grabTopZoneCharacter (number[i], &start, &mid, &end);
		printf("%c",start);

	for (int j = 0; j < scale; j++) {
		printf("%c", mid);
    	}

	printf("%c", end);

	for (int j = 0; j < scale; j++) printf("%c", ' ');
	i++;
  	}

	printf("\n");

}

// Outputs mid zones of all characters
void OutputMidZones (char *number)
{

  // Initialize index variables
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
// End of Initializing 

	char start;
	char mid;
	char end;

// print the mid sections of the numbers on new lines (scale - 1) times
	for (; i < scale - 1; i++)
  	{ 
		if (signBit == TRUE)
    		{
      			int lengthOffset = 2 * scale;
      			
			for (; k < lengthOffset; k++) printf(" ");
      				printf(" ");

    		}

	k = 0;

	if (signBit)
    	{
		j = 1;
	}

	while (number[j])
	{
		grabMidLevelChars (number[j], &start, &mid, &end); 
		printf("%c", start); // print the starting car

		for (int j = 0; j < scale; j++)
		{
			printf("%c", ' ');
		}

	printf("%c", end);

	for (int j = 0; j < scale; j++)
	{
		printf("%c", ' ');
	}

	j++;
	}

	j = 0; 
	printf("\n");

	}

	j = 0;

// Print out negative 
	if (signBit == TRUE)
	{
		int lengthOffset = 2 * scale;
		for (; k < lengthOffset; k++) printf("_");
			printf(" ");
	j = 1;
	}

	while (number[j])
	{ // print out the middle characters
		grabMidLevelChars (number[j], &start, &mid, &end);
		 printf("%c",start);

		for (int j = 0; j < scale; j++)
		{
			printf("%c", mid);
		}

		printf("%c", end);

		for (int j = 0; j < scale; j++)
		{
			printf("%c", ' ');
		}

		j++;

  	}

	printf(" \n");

}

// Print out bottom layer of all characters 
void OutputBottomZones (char *number)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;

	char start;
	char mid;
	char end;
	for (; i < scale - 1; i++)
	{

		if (signBit == TRUE)
		{
 			int lengthOffset = 2 * scale;
			for (; k < lengthOffset; k++)
				printf("%s", " ");
			
			putchar(' ');
		}

	k = 0;

	if (signBit == TRUE)
	{
		j = 1;
	}

	while (number[j])
	{
		grabBottomLevelChars (number[j], &start, &mid, &end);

	putchar(start);

	for (int j = 0; j < scale; j++)
	{
		printf("%c", ' ');
	}

	printf("%c", end);

	for (int j = 0; j < scale; j++)
	{
		printf("%c", ' ');
	}

	j++;
	}

	j = 0;
	putchar('\n');

	}
// End of while loop 

	if (signBit == TRUE)
	{
		int lengthOffset = 2 * scale;
	for (; k < lengthOffset; k++) printf(" ");

	printf(" ");
	j = 1;
	} else {
		j = 0;
	}

// While number at index j != 0 
	while (number[j])
	{
		grabBottomLevelChars (number[j], &start, &mid, &end);
		putchar(start);

	for (int j = 0; j < scale; j++) 
	{
		printf("%c", mid);
	}

	printf("%c", end);

	for (int j = 0; j < scale; j++)
	{
		printf(" ");
	}

	j++;

	}

	putchar(' ');
}

// prints out top level character on a per-digit basis

void grabTopZoneCharacter (char num, char * start, char * mid, char * end)
{ 
	if (num == '1' || num == '4')
	{
		*start = ' ';
		*mid = ' ';
		*end = ' ';
	} else
	{
	*start = ' ';
	*mid = '_';
	*end = ' ';
	}
}

// prints out mid level character on a  per-digit basis

void grabMidLevelChars (char num, char * start, char * mid, char * end)
{
	if (num == '1')
	{
		*start = '|';
		*mid = ' ';
		*end = ' ';
	} else if (num == '2' || num == '3')
	{
		*start = ' ';
		*mid = '_';
		*end = '|';
	} else if (num == '4' || num == '8' || num == '9')
	{
		*start = '|';
		*mid = '_';
		*end = '|';
	} else if (num == '5' || num == '6')
	{
		*start = '|';
		*mid = '_';
		*end = ' ';
	} else if (num == '7')
	{
		*start = ' ';
		*mid = ' ';
		*end = '|';
	} else
	{
		*start = '|';
		*mid = ' ';
		*end = '|';
	}
}

// prints out bottom level character on a per-digit basis
void grabBottomLevelChars (char num, char * start, char * mid, char * end)
{
	if (num == '1')
	{
		*start = '|';
		*mid = ' ';
		*end = ' ';
	} else if (num == '2')
	{
		*start = '|';
		*mid = '_';
		*end = ' ';
	} else if (num == '3' || num == '5' || num == '9') 
	{
		*start = ' ';
		*mid = '_'; 
		*end = '|';
	} else if (num == '4' || num == '7')
	{
    
		*start = ' ';
		*mid = ' ';
		*end = '|';
	} else {
	*start = '|';
	*mid = '_';
	*end = '|';
	}
}

// Convert character to decimal int data type 
unsigned int toDecimal(int base, char *number)
{
	int decimalValue = 0;
	int numLen = strlen(number);
	int i;

	for (i = 0; i < numLen; i++)
	{
		int currentCharVal = (digitValue(number[numLen - 1 - i], base));
		decimalValue += (power (base, i)) * currentCharVal;
	}

	return decimalValue;
}

// Returns digit value
int digitValue(char digit, int base)
{

	int value = base;

	if (digit >= '0' && digit <= '9')
		value = digit - '0';

	if (value < base) return value;

	printf("Bad scale\n");
	exit(1);
	return value;
}

// return which power
int power (int base, int exp)
{

	if (exp == 0)
	{
		return -1;
	}

	int result = 1;

	while (exp)
	{
		result = result * base;
		exp--;
	}

	return result;
}
