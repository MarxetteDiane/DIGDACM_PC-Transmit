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
#include "parityCalculation.h"
#define MAX 256000

char *readFile(char *fileName);
unsigned long binaryToDecimal(char *binary, int length);
void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);
char *strrev(char *str);

// INPUT: /Users/marxette/Desktop/DIGDACM/input.txt
// OUTPUT: /Users/marxette/Desktop/DIGDACM/output.txt

int main(void) {
    FILE *fp1, *fp2;
    char inFile[MAX], outFile[MAX], output[MAX];
    //int i, j;
    char * fullText = (char *) malloc(440); //* string = (char *) malloc(440);
    //const char *arr[strlen(fullText)];                                       //blocks are stored here
    //char stream[MAX]="";
    char *binary;
    int textLength, binaryLength;
    
    //get the input file name from the user
    printf("Enter your input file name: ");
    scanf("%s", inFile);

    // get the output filename from the user
    printf("Enter your output file name: ");
    scanf("%s", outFile);

    // open the source file in read mode
    fp1 = fopen(inFile, "r");

    // error handling
    if (!fp1) {
            printf("Unable to open the input file!!\n");
            return 0;
    }

    // open the target file in binary write mode
    fp2 = fopen(outFile, "wb");

    // error handling
    if (!fp2) {
            printf("Unable to open the output file!!\n");
            return 0;
    }
    
    // reads and gets data from input file
    fullText = readFile(inFile);
    printf("\n%s\n",fullText);
    /*--------------------------*/
    textLength = sizeof(fullText);
    binaryLength = textLength * 9;      // 8 binary digits + 1 space separator
    binary = malloc(binaryLength + 1);  // + 1 null terminator
    if(binary == NULL)
        exit(1);
    
    textToBinary(fullText, textLength, binary, binaryLength);
    printf("Your binary encoding is:\n%s\n", binary);
    
    /*--------------------------*/
    // converts data to binary
    /*for (i = 0; i < strlen(fullText); i++) {
        for (j = 0; j < 8; j++) {
            string[j] = (fullText[i] & (1 << j)) ? '1' : '0';
        }
        string[j]=' ';                              // separator between blocks
        
        strrev(string);                             // reverses binary
        arr[i] = string;                            // stores binary into an array
        
        strcat(stream, arr[i]);                     // concatenates elements of array to form stream of data
    }*/
    
    strcpy(output,parityCheck(binary));             // 2D Parity Calculation: gets data stream with appended parity bits
    printf("\n%s\n",output);
    
    free(binary);
    
    // close files
    fclose(fp1);
    fclose(fp2);
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
