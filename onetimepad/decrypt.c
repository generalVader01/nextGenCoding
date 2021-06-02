#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	char plaintext[1024], privateKey[1024], ciphertext[1024], escape;
	int length = 0, z;

	printf("Enter key: ");
        fgets(privateKey, sizeof(privateKey), stdin);
	printf("Enter Ciphertext: ");
	fgets(ciphertext, sizeof(ciphertext), stdin);
	
	while(escape == 0)
	{
		if(privateKey[length] == 32)
		{
		
		} else if(privateKey[length] < 'A' || privateKey[length] > 'Z')
		{
			escape = 1;
			length--;
		}

		length++;
	}



	printf("Decrypted message: "); 
	

	for(int i = 0; i < length; i++)
	{
		if(ciphertext[i] == 32)
		{
			z = ' ';
		} else if(ciphertext[i] >= privateKey[i])
		{
			z = (ciphertext[i] - privateKey[i]) + 'A';
		} else if (privateKey[i] > ciphertext[i])
		{
			z = (ciphertext[i] - privateKey[i]) + 'A' + 26;
		}
		putchar(z);
		plaintext[i] = z;
	}
	
	putchar('\n'); 

	return 0;
}	
