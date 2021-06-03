#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	char plaintext[1024], privateKey[1024], ciphertext[1024], crib[1024]; 
	int length = 0;

	time_t t; 
	srand ( (unsigned) time(&t));
	printf("Enter plaintext: ");
	scanf("%[^\n]", plaintext);

	for(int i = 0; i < sizeof(ciphertext); i++)
	{
		ciphertext[i] = (privateKey[i] ^ plaintext[i]);
		putchar(i);
	}

	printf("Ciphertext: ");

	for(int i = 0; i < length; i++)
	{
		putchar(ciphertext[i]);
	}

	putchar('\n');
	




	return 0;
}
