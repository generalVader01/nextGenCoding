#include <math.h> 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LEN 40
#define MAX_WORDS 110000
#define TRUE 1 
#define FALSE 0 
#define ZERO 0 

// function declaration 
void destroyNewLineCharacter (char *ch);
void outputWords(int a, int length);
void toLowerCase (char *ch);
void loadWordList (char *fileName, int *i);
int returnMinimumDistance (int *a, int length);
int hammingDistance (char *a, char *b, int length);
/// END of function declarations 
char wordlist[MAX_WORDS][MAX_WORD_LEN]; // Word array

// Main of the program -- Contains bulk of program instructions 
int main (int argc, char *argv[])
{

  // Checks required arguments
  if (argc == 1)
  {
      printf("Program needs to be run with at least one argument\n");         
      printf("Usage: ./spellChecker <$wordlist>\n"); 
      return 0;     
  }

  int i; 
  int lineCount = 0; // number of words in file

  loadWordList(argv[1], &lineCount); // load words from argument 2 of the commandline 

  char word[MAX_WORD_LEN]; // initializing the array that will be used as the input word
  char workingWord[MAX_WORD_LEN]; // initializing the array for word to be parsed

  printf("Enter nothing to terminate(no word)\n");
  printf("Enter word:\t\n"); // prompt user for word 
  while (fgets(word, MAX_WORD_LEN, stdin))
  { //grab line from standard input and store it in word
	
 	// If no word is supplied, exit the program
    if ((strlen(word) == 1) || (strlen(word) == 0 ))
    {
	      printf("\t\t***BYE***\n"); 
	      return 0;
    } 
	
    destroyNewLineCharacter(word); 
    int wordlength = strlen(word); // Gets length of input word
    toLowerCase(word); //converts word to lower case via function call
    int hammingDistancesList[lineCount]; // array of corrospoding hamming distances between dictionary words and input word
    int match = -1;

    for (i = 0; i < lineCount; i++)
    { 

      strcpy(workingWord, wordlist[i]); // Assigns wordlist of index i to the workingWord
      destroyNewLineCharacter(workingWord); int workingWordlength = strlen(workingWord) - 1; 
	// Get length of dictionary word
      toLowerCase(workingWord); //covert dictionary word to lowercase
      if (workingWordlength == wordlength)
      { // if length equals workingWordLen
        int dis = hammingDistance(word, workingWord, wordlength);
	// Calculates hamming distance between word and workingWord
        if (dis == 0)
        { 
        match = i; // if equal, store position of equal word
        }
        hammingDistancesList[i] = dis; // store hamming distance in corrospoding hamming distance array position

      } else if (abs(workingWordlength - wordlength) == 1) { 
        // if the length between word and workingWord is only one character different

          int dis = MAX_WORD_LEN; // initializing dis as the maximum theorectical distance
          int smallStrlength;
          int bigStrlength;

          if (workingWordlength > wordlength)
          { // figures out which word is longer and assigns length
            smallStrlength = wordlength;
            bigStrlength = workingWordlength;
          } else {
            smallStrlength = workingWordlength;
            bigStrlength = wordlength;          
          }

          char smallStr[smallStrlength];
          char bigStr[bigStrlength];

          if (workingWordlength > wordlength)
          { // Creates smaller and bigger strings, so we know which is which
            strcpy(smallStr, word);
            strcpy(bigStr, workingWord);
          } else {
            strcpy(smallStr, workingWord);
            strcpy(bigStr, word);
          }

          char bigStrCopy[bigStrlength];
          char smallStrCopy[smallStrlength];
          strcpy(bigStrCopy, bigStr);
          strcpy(smallStrCopy, smallStr);
	  int j, k; 

          for (j = 0; j < bigStrlength; j++)
          { // index the big string
            int pos = 0;
            bigStrCopy[j] = '\0'; // places NULL byte at index of j in the Big String

            for (k = 0; k < bigStrlength; k++) { // Creates string 
              if (bigStrCopy[k] != '\0' && pos < smallStrlength) {

                smallStr[pos] = bigStrCopy[k];
                pos++;

              }
            }

            strcpy(bigStrCopy, bigStr); // restore to old string
            int tempDis = hammingDistance(smallStr, smallStrCopy, smallStrlength) + 1; 
            if (dis > tempDis) dis = tempDis;                                       
          }                                                                       

          hammingDistancesList[i] = dis;

      } else { //assigns hammingDistance position to hammingDistance position
        hammingDistancesList[i] = MAX_WORD_LEN;
      }

    }

    int min = returnMinimumDistance (hammingDistancesList, lineCount);

    if (match != -1)
    { // if match was found, print out match

      printf("%s\n", word);

    } else if (!(min >= 40)) { // Prints out 10 closest words by hamming distance

      int wordCount = 0;
      int position = 0;

      while (wordCount < 10 && position < lineCount)
	    {
        if (hammingDistancesList[position] == min)
	      {
          printf("%s", wordlist[position]);
          wordCount++;
        }
        position++;
      }
    }

    printf("Enter word:\t"); // reprompt for word

  }

  return 0;
}

void loadWordList (char *fileName, int *count)
{ // this function loads words from file into array and counts words as it goes
  int i = 0;
  FILE *input = fopen(fileName, "r");
  while (fgets(wordlist[i], MAX_WORD_LEN, input)) 
  {
  i++;
  } // index file and add words to array
  *count = i; // increment count
}

int hammingDistance (char *a, char *b, int length)
{ // this function calculates hammingDistances
    
  /*
  int hammingDistance = 0;
  for (int i = 0; i < length; i++) 
  {
  if (a[i] != b[i]) 
    hammingDistance++; // index each string, every time a[i] DOES NOT EQUAL  b[i], increment distance by 1
  }
  return hammingDistance;*/

int hammingDistance = 0; // Runs for every character and checks to see if they are equal.
  // Also hammingdistance is increased if the mismatched character is not within one key of the correct
  // keyword (ex: 'i' is one key away from 'k')
  // Runs while the length of the word to be searched is still valid
  for (int i = 0; i < length; i++) 
  {
  if (a[i] != b[i]) {
      if ( (a[i] == 'a') && ((b[i] != 'q' || b[i]) != 'w' || b[i] != 's' || b[i] != 'z'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'q') && ((b[i] != 'w' || b[i]) != 'a' || b[i] != 's'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'z') && ((b[i] != 'a' || b[i]) != 's' || b[i] != 'z'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'w') && ((b[i] != 'q' || b[i]) != 'e' || b[i] != 'a' || b[i] != 's' || b[i] != 'd' ))  
      {
      hammingDistance++; 
      }     
      if ( (a[i] == 's') && ((b[i] != 'q' || b[i] != 'w' || b[i] != 'e' || b[i] != 'z') || b[i] != 'a' || b[i] != 'd' || b[i] != 'x' || b[i] != 'c'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'x') && ((b[i] != 'z' || b[i]) != 'c' || b[i] != 'a' || b[i] != 's' || b[i] != 'd'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'e') && ((b[i] != 'w' || b[i]) != 'r' || b[i] != 's' || b[i] != 'd' || b[i] != 'f'))  
      {
      hammingDistance++; 
      }    
      if ( (a[i] == 'd') && ((b[i] != 'w' || b[i] != 'e' || b[i] != 'r' || b[i] != 's') || b[i] != 'f' || b[i] != 'x' || b[i] != 'c' || b[i] != 'z'))  
      {
      hammingDistance++; 
      }
    
      if ( (a[i] == 'c') && ((b[i] != 'x' || b[i] != 'v' || b[i] != 's' || b[i] != 'd') || b[i] != 'f'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'r') && ((b[i] != 'e' || b[i] != 't' || b[i] != 'd' || b[i] != 'f') || b[i] != 'g'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'f') && ((b[i] != 'e' || b[i] != 'r' || b[i] != 't' || b[i] != 'd') || b[i] != 'g' || b[i] != 'c' || b[i] != 'v' || b[i] != 'b'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'v') && ((b[i] != 'c' || b[i] != 'b' || b[i] != 'd' || b[i] != 'f') || b[i] != 'g'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 't') && ((b[i] != 'r' || b[i] != 'y' || b[i] != 'f' || b[i] != 'g') || b[i] != 'h'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'g') && ((b[i] != 'r' || b[i] != 't' || b[i] != 'y' || b[i] != 'f') || b[i] != 'h' || b[i] != 'v' || b[i] != 'b' || b[i] != 'n'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'b') && ((b[i] != 'v' || b[i] != 'n' || b[i] != 'f' || b[i] != 'g') || b[i] != 'h'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'y') && ((b[i] != 't' || b[i] != 'u' || b[i] != 'g' || b[i] != 'h') || b[i] != 'j'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'h') && ((b[i] != 't' || b[i] != 'y' || b[i] != 'u' || b[i] != 'g') || b[i] != 'j' || b[i] != 'b' || b[i] != 'n' || b[i] != 'm'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'n') && ((b[i] != 'g' || b[i] != 'h' || b[i] != 'j' || b[i] != 'b') || b[i] != 'm'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'u') && ((b[i] != 'y' || b[i] != 'i' || b[i] != 'h' || b[i] != 'j') || b[i] != 'k'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'j') && ((b[i] != 'y' || b[i] != 'u' || b[i] != 'i' || b[i] != 'h') || b[i] != 'k' || b[i] != 'n' || b[i] != 'm' || b[i] != ','))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'm') && ((b[i] != 'n' || b[i] != ',' || b[i] != 'h' || b[i] != 'j') || b[i] != 'k'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'i') && ((b[i] != 'u' || b[i] != 'o' || b[i] != 'j' || b[i] != 'k') || b[i] != 'l'))  
      {
      hammingDistance++; 
      }

      if ( (a[i] == 'k') && ((b[i] != 'j' || b[i] != 'l' || b[i] != 'u' || b[i] != 'i') || b[i] != 'o' || b[i] != 'm' || b[i] != ','))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'o') && ((b[i] != 'i' || b[i] != 'p' || b[i] != 'k' || b[i] != 'l') || b[i] != ';'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'l') && ((b[i] != 'i' || b[i] != 'o' || b[i] != 'p' || b[i] != 'k') || b[i] != 'l' || b[i] != ';'))  
      {
      hammingDistance++; 
      }
      if ( (a[i] == 'p') && ((b[i] != 'o' || b[i] != 'l' || b[i] != ';' || b[i] != '[')))  
      {
      hammingDistance++; 
      }
	
// These series of statements will decrease the hammingDistance 
// if the two words have the exact same characters at the beginning of the word
// Example: If I misspelled programmer as "progrsmmer", the spellchecker
// would see that the first four characters are exactly the same 
// So that increases the odds of the fact that programmer is the most likely match
// So the hamming distance would be decreased by two
    if ( (a[i] == b[i]) && (a[i+1] == b[i+1]) && (a[i+2] == b[i+2])) 
    {
    hammingDistance--; 
    }

 if ( (a[i] == b[i]) && (a[i+1] == b[i+1]) && (a[i+2] == b[i+2]) && ( a[i+3] == b[i+3])) 
    {
    hammingDistance--;
    }
    
if ( (a[i] == b[i]) && (a[i+1] == b[i+1]) && (a[i+2] == b[i+2]) && ( a[i+3] == b[i+3]) 
	&& (a[i+4] == b[i+4]))
    {
    hammingDistance--;
    }

if ( (a[i] == b[i]) && (a[i+1] == b[i+1]) && (a[i+2] == b[i+2]) && ( a[i+3] == b[i+3]) 
       && ( a[i+4] == b[i+4]))
    {
    hammingDistance--;
    }

if ( (a[i] == b[i]) && (a[i+1] == b[i+1]) && (a[i+2] == b[i+2]) && ( a[i+3] == b[i+3])
       && ( a[i+4] == b[i+4]) && ( a[i+5] == b[i+5]))
    {
    hammingDistance--; 
    }

    hammingDistance++; // index each string, every time a[i] DOES NOT EQUAL  b[i], increment distance by 1
    }
  }
  return hammingDistance;

}

// Calculates minimium distance
int returnMinimumDistance (int *a, int length)
{
    int i = 1;
    int minimium = a[0];

    for (; i < length; i++)
    {
      if (a[i] < minimium) minimium = a[i];
    }

    return minimium;
}

  // Strips off new line character and replace it with null terminator character
  // This effectively tokenizes the entire string
void destroyNewLineCharacter (char *ch)
{

  int characterLength = strlen (ch);

  for (int i = 0; i < characterLength; i++)
  {
    if (ch[i] == '\n') ch[i] = '\0';
  }
}
// This functions does.. what else?
// Ensures that all values are lowercase using the toLower function
void toLowerCase (char *ch) {
  int i;
  int characterLength = strlen (ch);

  for (i = 0; i < characterLength; i++) {
    ch[i] = tolower(ch[i]);
  }
}
