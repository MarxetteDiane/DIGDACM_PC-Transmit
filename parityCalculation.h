//
//  parityCalculation.h
//  DIGDACM
//
//  Created by Marxette Diane Cabato on 9/10/20.
//  Copyright © 2020 Marxette Diane Cabato. All rights reserved.
//

#ifndef parityCalculation_h
#define parityCalculation_h

// INPUT: /Users/marxette/Desktop/DIGDACM/input.txt
// OUTPUT: /Users/marxette/Desktop/DIGDACM/output.txt

void concatenate(char p[], char q[]);

void parityCheck(char stream[]) {
    int i, one, z = 0, j = 0;
    //char *arr[4] = {"00101101","10110110","10011000","11110111"};
    char *arr[strlen(stream)/8];
    char straightStream[1000];
    straightStream[0] = '\0';
    
    char * token = strtok(stream, " ");
    // loop through the string to extract all other tokens
    i = 0;
    while( token != NULL ) {
        //printf( "%s", token ); //printing each token
        arr[i] = token;
        strcat(straightStream, token);
        token = strtok(NULL, " ");
        i++;
    }
    arr[i] = NULL;
    
    printf("\n%s",straightStream);
    for (i = 0; i < strlen(straightStream)/8; i++) {
        printf("\n%s",arr[i]);
    }
    
    char *combination = (char *) malloc(44);                    // Stream to be transmitted
    char parityBitsRight[100], parityBitsBottom[100];
    char *string = NULL, parityBit, newString[9];
    char twoD[strlen(straightStream)/8][8];       //Rows and Columns
    
    combination[0]='\0';
    parityBitsRight[0]='\0';
    parityBitsBottom[0]='\0';
    
    printf("\n\n");
    
    // ROW
    for (z = 0; z < strlen(straightStream)/8; z++) {
        one = 0;
        string = arr[z];
        for (i = 0; i < 8; i++) {
            if (string[i] == '1') {
                one++;
            }
            //insert bits into 2D array
            twoD[z][i] = string[i];
        }
        
        strcpy(newString,string);
        //check whether odd or even
        if (one % 2 == 0) {                 //even
            //strcat(newString,"0");
            concatenate(newString, "0");
            strcat(parityBitsRight,"0");
            parityBit = '0';
        } else {                            //odd
            //strcat(newString,"1");
            strcat(parityBitsRight,"1");
            concatenate(newString, "1");
            parityBit = '1';
        }
        
        strcat(combination,newString);
        printf("\n\n%s",string);
        printf("\n%i ones",one);
        printf("\nParity bit is %c",parityBit);
        printf("\nNew String is %s",newString);
    }
    
    printf("\nParity Bits Right: %s", parityBitsRight);
    
    one = 0;
    for (j = 0; j < 8; j++) {
        for (i = 0; i < strlen(straightStream)/8; i++) {
            if (twoD[i][j] == '1') {
                one++;
            }
        }
        
        if (one % 2 == 0) {
            strcat(parityBitsBottom, "0");
        } else {
            strcat(parityBitsBottom, "1");
        }
        one = 0;
    }
    
    for (i = 0; i < strlen(parityBitsBottom); i++) {
        if (parityBitsBottom[i] == '1') {
            one++;
        }
    }
    
    if (one % 2 == 0) {
        strcat(parityBitsBottom, "0");
    } else {
        strcat(parityBitsBottom, "1");
    }
    
    strcat(combination,parityBitsBottom);
    printf("\nFULL STRING: %s\n\n", combination);
    /*
    STEPS:
        Row:
            1. Get parity bits of each row.
        Column:
            1. Get parity for string[0] -> string[7] for arr[i].
            2. Get parity bit for the right side parity bits.
            
        Combination:
            1. newString arr[i].
    */
    
    free(combination);
}

void concatenate(char p[], char q[]) {
   int c = 0, d = 0;
    
   while (p[c] != '\0') {
      c++;
   }
 
   while (q[d] != '\0') {
      p[c] = q[d];
      d++;
      c++;
   }
   p[c] = '\0';
}

#endif /* parityCalculation_h */
