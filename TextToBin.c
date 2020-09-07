#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256

unsigned long binaryToDecimal(char *binary, int length);
void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);

int main(void)
{
	FILE *fp1, *fp2;
    char ch, inFile[MAX], outFile[MAX];
    char text[101];
    char *binary;
	int textLength, binaryLength;
	char * str = (char *) malloc(44);

    //get the input file name from the user
    printf("Enter your input file name:");
    scanf("%s", inFile);

    // get the output filename from the user
    printf("Enter your output file name:");
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
    
    while (!feof(fp1)) {
        fscanf(fp1, "%100[^\n]s", text);
		textLength = strlen(text);
	    binaryLength = textLength * 9;      // 8 binary digits + 1 space separator
	    binary = malloc(binaryLength + 1);  // + 1 null terminator
	    if(binary == NULL)
	        exit(1);
	    
	    textToBinary(text, textLength, binary, binaryLength);
	    fprintf(fp2, "%s", binary);
	    
	    free(binary);
    }
	
	fclose(fp1);
    fclose(fp2);
	return 0;
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
