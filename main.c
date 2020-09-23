//
//  main.c
//  DIGDACM
//
//  Created by Marxette Diane Cabato on 9/10/20.
//  Copyright © 2020 Marxette Diane Cabato. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256000

char *readFile(char *fileName);
unsigned long binaryToDecimal(char *binary, int length);
void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);
char *strrev(char *str);

// INPUT: /Users/marxette/XCode/DIGDACM/input.txt

int main(void) {
    FILE *fp1;
    char inFile[MAX];
    char * fullText = (char *) malloc(440); //* string = (char *) malloc(440);
    char *binary;
    int textLength, binaryLength;
    
    //get the input file name from the user
    printf("Enter your input file name: ");
    scanf("%s", inFile);

    // open the source file in read mode
    fp1 = fopen(inFile, "r");

    // error handling
    if (!fp1) {
            printf("Unable to open the input file!!\n");
            return 0;
    }
    
    // reads and gets data from input file
    fullText = readFile(inFile);
    
    //int fullLength = strlen(fullText);
    
    textLength = sizeof(fullText);
    binaryLength = textLength * 9;      // 8 binary digits + 1 space separator
    binary = malloc(binaryLength + 1);  // + 1 null terminator
    if(binary == NULL)
        exit(1);
    
    textToBinary(fullText, textLength, binary, binaryLength);

    printf("\n%s\n",binary);
    
    free(binary);
    
    // close files
    fclose(fp1);
    return 0;
}

char *readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL;            // could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // null terminator
    code[n] = '\0';

    return code;
}

void textToBinary(char *text, int textLength, char *binary, int binaryLength)
{
    char *octet = malloc(9);
    if(octet == NULL)
        exit(1);
    while(*text)
    {
        decimalToBinary(*text, octet);
        while(*octet)
            *binary++ = *octet++;
        *binary++ = ' ';
        ++text;
        octet -= 8;
    }
    *binary = '\0';
    binary -= binaryLength;
    free(octet);
}

void decimalToBinary(int decimal, char *octet)
{
    octet += 8;
    *octet = '\0';
    if(decimal == 0)
    {
        octet -= 8;
        octet = "00000000";
    }
    else
    {
        while(decimal > 0)
        {
            --octet;
            *octet = decimal % 2 + '0';
            decimal = decimal / 2;
        }
    }
    while(strlen(octet) < 8)
    {
        --octet;
        *octet = '0';
    }
}


// reverses string
char *strrev(char *str) {
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
