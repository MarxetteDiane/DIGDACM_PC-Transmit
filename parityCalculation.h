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
    char *blocks[strlen(stream)/8];                 // blocks of data
    char straightStream[1000];                      // continuous data stream without separator
    straightStream[0] = '\0';                       // removes unwanted characters at the beginning
    
    char * block = strtok(stream, " ");
    
    // loop through the string to extract data blocks
    i = 0;
    while( block != NULL ) {
        blocks[i] = block;
        strcat(straightStream, block);
        block = strtok(NULL, " ");
        i++;
    }
    blocks[i] = NULL;
    
    char *combination = (char *) malloc(44);                    // stream to be appended with parity bits
    char parityBitsRight[100], parityBitsBottom[100];
    char *string = NULL, parityBit, newString[9];
    char twoD[strlen(straightStream)/8][8];                     // binary data Rows and Columns
    
    combination[0]='\0';
    parityBitsRight[0]='\0';
    parityBitsBottom[0]='\0';
        
    // Right Parity Bits [ROWS]
    for (z = 0; z < strlen(straightStream)/8; z++) {
        one = 0;
        string = blocks[z];
        for (i = 0; i < 8; i++) {
            if (string[i] == '1') {
                one++;
            }
            //insert bits into 2D arrays
            twoD[z][i] = string[i];
        }
        
        strcpy(newString,string);
        
        // checks parity whether odd or even
        if (one % 2 == 0) {                                 // even: 0 parity bit
            concatenate(newString, "0");
            strcat(parityBitsRight,"0");
            parityBit = '0';
        } else {                                            // odd: 1 parity bit
            strcat(parityBitsRight,"1");
            concatenate(newString, "1");
            parityBit = '1';
        }
        
        // appends block with parity bit into stream
        strcat(combination,newString);
        
        // for checking
        /*printf("\n\n%s",string);
        printf("\n%i ones",one);
        printf("\nParity bit is %c",parityBit);
        printf("\nNew String is %s",newString);*/
    }
    
    one = 0;
    
    // Bottom Parity Bits [COLUMNS]
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
    
    // counts number of 1s in bottom parity bits
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
    printf("\n%s\n\n", combination);
    
    // frees malloc
    free(combination);
}

// DIY concatenate lol
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
