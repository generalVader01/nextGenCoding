#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
	char plaintext[1024], privateKey[1024], ciphertext[1024], escape = 0;
	int length = 0, whitespaces = 0;
	time_t t;
	srand( (unsigned) time(&t));

	printf("Enter plaintext: ");
	scanf("%[^\n]", plaintext);
	
	// converts undercase to uppercase
	for(int i = 0; i < sizeof(plaintext); i++)
	{
		if(plaintext[i] != ' ')
		{
			if(plaintext[i] >= 97)
				plaintext[i] -= 32; 
		}
	}

	/* Determines length */
	for(int i = 0; escape == 0; i++, length++)
	{
		if((plaintext[i] == 32))
			whitespaces++;
	
		if(!((plaintext[i] >= 'A' && plaintext[i] <= 'Z') || (plaintext[i] >= '0' && plaintext[i] <= '9') || (plaintext[i] == 32)))
		{
			escape = 1;
			length--;
		}
	}
	
	if(length <= 0 || length > sizeof(plaintext) || plaintext[0] == '\n')
	{
		printf("Length must be at least 1 and less than %ld characters", sizeof(plaintext));
		return -1;		
	 }

//	time_t t;
//	srand((unsigned) time(&t));
	
	printf("Key: ");
	
	for(int i = 0; i < length; i++)
	{
		if(plaintext[i] == 32)
		{
			privateKey[i] = ' ';
			putchar(privateKey[i]);
		} else {
			privateKey[i] = 'A' + (random() % 26);
			putchar(privateKey[i]);
		}
	}

	putchar('\n');

	for(int i = 0; i < length; i++)
	{
		if(plaintext[i] == 32)
		{
			ciphertext[i] = ' '; 
		} else {
			ciphertext[i] = (( (privateKey[i] - 'A') + (plaintext[i] - 'A')) % 26) + 'A'; 
		}
	}

	printf("Ciphertext: ");
	
	for(int i = 0; i < length; i++)
	{
		putchar(ciphertext[i]);
	}

	putchar('\n');
	
	return 0;	
}
