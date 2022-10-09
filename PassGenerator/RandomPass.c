#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define UPPERCASE TRUE
#define UNDERCASE TRUE
#define NUMBERS TRUE
#define SYMBOLS TRUE
#define SPACES TRUE

// ***** Summary ***** 
// Generates a psudo random string of characters. 
// Can be used to generate multiple passwords, seperated by newlines
// No max limit to length.

// ***** ChangeLog *****
/*
 * 1.01: Added the space character to the generate list
 * 1.02: Fixed return values. Errors are now returning negative 1. 0 is returned only for success
 * 1.03: Removed Magic Number for the Character Source List for Generation. It is now defined as a variable
 * 1.04: Changed input from signed int to unsigned int.
 * 1.05: included limits library. Now checking to make sure that specified input does not exceed limits of data type
 * 1.06: Big update. Added options to enable spaces, symbols, numbers, uppercase, and undercase in the charset. 
*/

int main(int argc, char *argv[]) {

	if (argc != 3)
	{
		printf("Usage: ./RandomPass $NumberOfPasswords $PasswordLength\n");
		return -1;
	}
	
	// note: randomLetter array is declared as size 95 because that is the max possible size with all character types enabled
	unsigned char genLength = 0;
	unsigned char randomLetters[95];
	unsigned int passGenerations = atoi(argv[1]);
	unsigned int randomWordLength = atoi(argv[2]);

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
	
	// Add a Space if enabled 	
	if(SPACES == TRUE)
	{
		randomLetters[genLength] = ' ';
		genLength++;
	}

	// Adds symbols if enabled
	if(SYMBOLS == TRUE)
	{
		for(int i = 33; i <= 47; i++, genLength++)
		{
			randomLetters[genLength] = (char) i;
	        }

		for(int i = 58; i <= 64; i++, genLength++)
		{
			randomLetters[genLength] = (char) i;
		}
		
		for(int i = 91; i <= 96; i++, genLength++)
		{
			randomLetters[genLength] = (char) i;
		}

		for(int i = 123; i <= 126; i++, genLength++)
		{
			randomLetters[genLength] = (char) i;
		}
 	}
	

	// Adds numbers if enabled
	if(NUMBERS == TRUE)
        {
                for(int i = 48; i <= 57; i++, genLength++)
                {
                	randomLetters[genLength] = (char) i;
                }
        }

	// Adds uppercase if enabled	
	if(UPPERCASE == TRUE)
        {
                for(int i = 65; i <= 90; i++, genLength++)
                {
                        randomLetters[genLength] = (char) i;
                }
        }
	
	// Add undercase if enabled
	if(UNDERCASE == TRUE)
	{	
		for(int i = 97; i <= 122; i++, genLength++)
		{
			randomLetters[genLength] = (char) i;
		}
	}

	time_t t;
	srand((unsigned) time(&t));

	// Generates random passwords
	
	for(int l = 0; l < passGenerations; l++)
	{
		for(int i = 0; i < randomWordLength; i++)
		{
			printf("%c", randomLetters[rand() % genLength]);
					
		}
		printf("\n");
	}
	
	return 0;
}

