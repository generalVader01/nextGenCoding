#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

	if (argc != 3)
	{
		printf("Usage: ./RandomPass $NumberOfPasswords $PasswordLength\n");
		return 0;
	}

	char randomLetters[69];
	int randomWordLength = atoi(argv[2]);
	int passGenerations = atoi(argv[1]);
	
	if(randomWordLength <= 0 || passGenerations <= 0)
	{
		printf("Length must be at least 1\n");
		return 0;
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

	time_t t;
	srand((unsigned) time(&t));

	// Generates random passwords
	
	for(int l = 0; l < passGenerations; l++)
	{
		for(int i = 0; i < randomWordLength; i++)
		{
			printf("%c", randomLetters[rand() % 69]); 
		}
		printf("\n");
	}
	
	return 0;
}
