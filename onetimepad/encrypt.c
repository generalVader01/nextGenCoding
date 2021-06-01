/*
 * Read in the plaintext
 * Check that the length is at least 1
 * Check that it's all upper case
 * Determine length of the plaintext
 * Generate private key (forcing it to be the same length as the plaintext) 
 * Set up an Array of A-Z and the space character, with A = 1, Z = 26, and ' ' = 27
 * Add private key array index with the index of the plaintext, modulus 27
 * Print out encrypted message
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	char plaintext[1024], privateKey[1024], ciphertext[1024];
	
	printf("Enter plaintext: ");
	scanf("%[^\n]", plaintext);
	
	// converts undercase to uppercase
	for(int i = 0; i < strlen(plaintext); i++)
	{
		if(plaintext[i] != ' ')
		{
			if(plaintext[i] >= 97)
				plaintext[i] -= 32; 
		}
	}

	char escape = 0;
	int length = 0;

	for(int i = 0; escape == 0; i++, length++)
	{
	
		if(isspace(plaintext[i]))
			length--;

	
		if(!((plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= '0' && plaintext[i] <= '9') || isspace(plaintext[i])))
		{
			escape = 1;
		}
	}
	
	time_t t;
	srand((unsigned) time(&t));
	
	length--;
	
	printf("Length: %d\n", length);
	printf("Private Key: ");
	
	for(int i = 0; i < length; i++)
	{
		privateKey[i] = 'A' + (random() % 26);
		putchar(privateKey[i]);
	//	printf("%d", privateKey[i]);
	}
	
	
	printf("\n");

	for(int i = 0; i < length; i++)
	{
		if(plaintext[i] == 32)
		{
			ciphertext[i] = 32; 
		} else {
			//ciphertext[i] = (table[ ((privateKey[i] - 65) + (plaintext[i] - 65))  % 26] ) ;	
			ciphertext[i] = (( (privateKey[i] - 'A') + (plaintext[i] - 'A')) % 26) + 'A'; 
		}
	}

	printf("Ciphertext : ");
	
	for(int i = 0; i < length; i++)
	{
		printf("%c", ciphertext[i]);
	//	printf("%d", ciphertext[i]);
	}

	putchar('\n');
	
		
	printf("Decrypt: ");
	
	for(int i = 0; i < length; i++)
	{
		int z = 0;
	        //printf("Ciphertext: %d, privateKey: %d\n", ciphertext[i], privateKey[i]);

		if(ciphertext[i] > privateKey[i])
		{
			z = (ciphertext[i] - privateKey[i]) + 'A';
		} else if (privateKey[i] > ciphertext[i])
		{
			z = (ciphertext[i] - privateKey[i])  + 'A' + 26;		
		} else if (ciphertext[i] == privateKey[i])
		{
			z = (privateKey[i] - ciphertext[i]) + 'A';
		} else {

		printf("Something is quite wrong.\n");
		}

		putchar(z);
	}

	putchar('\n'); 
	
	
	return 0;	
}
