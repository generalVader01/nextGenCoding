/* ***** SUMMARY *****
 * Takes in a sentence and transforms it into Morse Code
 *
 * ***** CHANGELOG *****
 * 1.0: Base program made. Changed gets to fgets
 *
 * ***** KNOWN ISSUES *****
 * 1) The program is currently unable to translate symbols into morse code
 * 2) It seems unable to handle translations of less than 4 characters
 * 3) It doesn't handle empty input
*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 1000

int main(void)
{
	char *alphamorse[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
        	"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
     		"...-",".--","-..-","-.--","--.."};
	
	char *nummorse[]={"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};
 
	register i = 0;
	char str[MAX];

	printf("Enter a sentence: ");
	
        str[0] = '\0';

	fgets(str, MAX, stdin); 
	
	putchar('\n');

	if(str[0] == '\0')
	{
		printf("You need to enter some input\n");
		return -1;
	}
	
	while(str[i] != '\0')
	{
	
	
		if(str[i] != ' ' && (!isdigit(str[i])))  
 		{
			printf("%s ", alphamorse[toupper(str[i]) - 65]);  
 		}

	if(str[i]==' ')
    	{
     		putchar('\n');
    	}

	if(isdigit(str[i])&&str[i]!=' ')
    	{
     		 printf("%s ",nummorse[str[i]-48]);    
    	}
    
       	i++;
	}

putchar('\n');

return 0;
}
