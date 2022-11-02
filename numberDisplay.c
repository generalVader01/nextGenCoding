/*
Prints out numbers in big form
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_LENGTH 100
#define TRUE 1
#define FALSE 0

// Declared Functions 
unsigned int toDecimal(int base, char * number); // define used functions
int digitValue(char digit, int base);
int power(int base, int exp);
void OutputTopZones(char * number);
void OutputMidZones(char * number);
void OutputBottomZones(char * number);
void grabTopZoneCharacter(char num, char * start, char * mid, char * end);
void grabMidLevelChars(char num, char * start, char * mid, char * end);
void grabBottomLevelChars(char num, char * start, char * mid, char * end);
// END of function declaration 

int signBit = FALSE; // boolean used to indicate wheather or not the input number is negative
int scale = 1; // scale the the numbers will be printed to

int main(int argc, char * argv[]) {
    if ((argc == 1 || argc > 3)) {
        printf("You need to run the program with at least one argument\n");
        printf("Usage:\t \"./assignment3 <$number> <$optional_scale>\"\n");
        printf("Example:\t \"./assignment3 420\"\n");
        printf("Type \"./assignment3 help\" for more information about the program\n");
        return 0;
    }

    char num[NUMBER_LENGTH];
    strcpy(num, argv[1]); // Stores first argument into string
    if (num[0] == '-') signBit = TRUE; // Test if input number is negative
    if (num[0] == '+') signBit = FALSE; // Test if input number is postive

    if (argc > 2) {
        scale = toDecimal(10, argv[2]); // initialize scale to argv[2] 
    }
    // Scale of zero will return nothing but a new line character 

    if (scale == 0) {
        printf("\n");
        return -1;
    }

    if (scale < 1) { // validate scale value
        printf("Invalid scale value\n");
        return 0;
    }
    // Forces scale between 1 and 5 inclusive 
    if (scale > 5) {
        printf("Scale must be 1-5\n");
        return 0;
    }

    unsigned int index = 0;

    if (signBit) {

        if (num[1] == 0) {
            printf("Wrong digit value\n");
            return 0;
        }

        index++;
    }

    while (num[index]) {

        // checks to make sure input is a number; not a character or string

        if (!(num[index] > 47 && num[index] < 58)) {
            printf("Enter a valid number\n");
            printf("Example: ./assignment3 100\n");
            return 0;
        }

        index++;
    }

    OutputTopZones(num); // print top zone
    OutputMidZones(num); // print mid zone
    OutputBottomZones(num); // print bottom zone
    printf("\n"); // Print new line character
    return 0;
}

// Prints top zones of all numbers 
void OutputTopZones(char * number) {
    unsigned int i = 0;

    char start;
    char mid;
    char end;

    if (signBit == TRUE) {
        int lengthOffset = 2 * scale;
        for (; i < lengthOffset; i++) printf(" ");
        printf(" ");
    }

    if (signBit == TRUE) {
        i = 1;
    } else {
        i = 0;
    }

    while (number[i]) {
        grabTopZoneCharacter(number[i], & start, & mid, & end);

        printf("%c", start);

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
void OutputMidZones(char * number) {

    // Initialize index variables
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    // End of Initializing 

    char start;
    char mid;
    char end;

    // print the mid sections of the numbers on new lines (scale - 1) times
    for (; i < scale - 1; i++) {

        if (signBit == TRUE) {
            int lengthOffset = 2 * scale;
            for (; k < lengthOffset; k++) printf(" ");
            printf(" ");

        }

        k = 0;

        if (signBit) {
            j = 1;
        }

        while (number[j]) { // Read input string
            grabMidLevelChars(number[j], & start, & mid, & end);
            // for each digit: 
            //  get the begining, middle and ending char

            printf("%c", start); // print the starting car

            for (int j = 0; j < scale; j++) { // print the middle char J times
                printf("%c", ' ');
            }

            printf("%c", end);
            // Print the last char

            for (int j = 0; j < scale; j++) {
                printf("%c", ' ');
            }

            j++; // Add one to j 
        }

        j = 0; // Reset j 
        printf("\n"); // New line 

    }

    j = 0;

    // Print out negative 
    if (signBit == TRUE) {
        int lengthOffset = 2 * scale;
        for (; k < lengthOffset; k++) printf("_");
        printf(" ");
        j = 1;
    }

    while (number[j]) { // print out the middle characters
        grabMidLevelChars(number[j], & start, & mid, & end);

        printf("%c", start);

        for (int j = 0; j < scale; j++) {
            printf("%c", mid);
        }

        printf("%c", end);

        for (int j = 0; j < scale; j++) {
            printf("%c", ' ');
        }

        j++;

    }

    printf(" \n"); // NEW LINE

}
// Print out bottom layer of all characters 
void OutputBottomZones(char * number) {
    // Same syntax as before 
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;

    char start;
    char mid;
    char end;
    // End of initialization 
    for (; i < scale - 1; i++) {

        if (signBit == TRUE) {
            int lengthOffset = 2 * scale;
            for (; k < lengthOffset; k++) printf("%s", " ");
            printf("%s", " ");

        }

        k = 0;

        if (signBit == TRUE) {
            j = 1;
        }

        while (number[j]) {
            grabBottomLevelChars(number[j], & start, & mid, & end);

            printf("%c", start);

            for (int j = 0; j < scale; j++) {
                printf("%c", ' ');
            }

            printf("%c", end);

            for (int j = 0; j < scale; j++) {
                printf("%c", ' ');
            }

            j++;
        }

        j = 0;
        printf("%c", '\n');

    }
    // End of while loop 

    if (signBit == TRUE) {
        int lengthOffset = 2 * scale;
        for (; k < lengthOffset; k++) printf(" ");
        printf(" ");
        j = 1;
    } else {
        j = 0;
    }

    // While number at index j != 0 
    while (number[j]) {
        grabBottomLevelChars(number[j], & start, & mid, & end);

        printf("%c", start);

        for (int j = 0; j < scale; j++) {
            printf("%c", mid);
        }

        printf("%c", end);

        for (int j = 0; j < scale; j++) {
            printf(" ");
        }

        j++;

    }

    printf(" ");

}
// prints out top level character on a 
// per-digit basis
void grabTopZoneCharacter(char num, char * start, char * mid, char * end) { // 
    if (num == '1' || num == '4') {
        * start = ' ';
        * mid = ' ';
        * end = ' ';
    } else {
        * start = ' ';
        * mid = '_';
        * end = ' ';
    }
}
// prints out mid level character on a 
// per-digit basis
void grabMidLevelChars(char num, char * start, char * mid, char * end) { // returns bottom chars for any given digit
    if (num == '1') {
        * start = '|';
        * mid = ' ';
        * end = ' ';
    } else if (num == '2' || num == '3') {
        * start = ' ';
        * mid = '_';
        * end = '|';
    } else if (num == '4' || num == '8' || num == '9') {
        * start = '|';
        * mid = '_';
        * end = '|';
    } else if (num == '5' || num == '6') {
        * start = '|';
        * mid = '_';
        * end = ' ';
    } else if (num == '7') {
        * start = ' ';
        * mid = ' ';
        * end = '|';
    } else {
        * start = '|';
        * mid = ' ';
        * end = '|';
    }
}

// prints out bottom level character on a 
// per-digit basis
void grabBottomLevelChars(char num, char * start, char * mid, char * end) {
    if (num == '1') {
        * start = '|';
        * mid = ' ';
        * end = ' ';
    } else if (num == '2') {
        * start = '|';
        * mid = '_';
        * end = ' ';
    } else if (num == '3' || num == '5' || num == '9') {
        * start = ' ';
        * mid = '_';
        * end = '|';
    } else if (num == '4' || num == '7') {
        * start = ' ';
        * mid = ' ';
        * end = '|';

        // an invalid digit
    } else {
        * start = '|';
        * mid = '_';
        * end = '|';
    }
}

// To Decimal 
unsigned int toDecimal(int base, char * number) {
    int decimalValue = 0;
    int numLen = strlen(number);
    int i;

    for (i = 0; i < numLen; i++) {
        int currentCharVal = (digitValue(number[numLen - 1 - i], base));
        decimalValue += (power(base, i)) * currentCharVal;
    }

    return decimalValue;
}

// Returns digit value
int digitValue(char digit, int base) {

    int value = base;

    if (digit >= '0' && digit <= '9')
        value = digit - '0';

    if (value < base) return value;

    printf("Wrong  scale\n");
    exit(1);
    return value;
}

// return which power
int power(int base, int exp) {

    if (exp == 0) {
        return 1;
    }

    int result = 1;

    while (exp) {
        result = result * base;
        exp--;
    }

    return result;
}
