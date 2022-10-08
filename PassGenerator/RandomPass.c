#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define Gen_Array_Length 70 

// ***** Summary ***** 
// Generates a psudo random string of characters. 
// Can be used to generate multiple passwords, seperated by newlines
// No max limit to length.

// ***** ChangeLog *****
/*
 * 1.01: Added the space character to the generate list
 * 1.02: Fixed return values. Errors are now returning negative 1. 0 is returned only for success
 * 1.03: Removed Magic Number for the Character Source List for Generation. It is now defined as a variable
 * 1.04: Changed input from signed int to unsigned int
 * 1.05: included limits library. Now checking to make sure that specified input does not exceed limits of data type
*/

int main(int argc, char *argv[]) {

	if (argc != 3)
	{
		printf("Usage: ./RandomPass $NumberOfPasswords $PasswordLength\n");
		return -1;
	}

	char randomLetters[Gen_Array_Length];
	unsigned int randomWordLength = atoi(argv[2]);
	unsigned int passGenerations = atoi(argv[1]);


	if(randomWordLength <= 0 || passGenerations <= 0)
	{
		printf("Length must be at least 1\n");
		return -1;
	}
	
	// This if statement is currently unreachable. A unsigned int can never overflow. It is reduced by modulus UINT_MAX. So UINT_MAX + 1 = 0
	if(randomWordLength > UINT_MAX || passGenerations > UINT_MAX)
	{
		printf("Your input has exceeded the limits of the unsigned int data type\n");
	        printf("Please specify a input value less than %u\n", UINT_MAX);
		return -1;
	}	

/* Some symbols + letters A-Z in the ASCII table */

	for(int i = 0; i < 43; i++)
	{
		randomLetters[i] = (char) (48 + i);
	}

/* Builds letters a-z (undercase) in the ASCII table */

	for(int i = 43; i < 69; i++)
	{
		randomLetters[i] = (char) (54 + i);
	}
/* Add Space Character */

randomLetters[Gen_Array_Length - 1] = (char) 32;


	time_t t;
	srand((unsigned) time(&t));

	// Generates random passwords
	
	for(int l = 0; l < passGenerations; l++)
	{
		for(int i = 0; i < randomWordLength; i++)
		{
			printf("%c", randomLetters[rand() % Gen_Array_Length]);
					
		}
		printf("\n");
	}
	
	return 0;
}

