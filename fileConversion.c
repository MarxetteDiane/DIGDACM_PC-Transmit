#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256

char *readFile(char *fileName);

int main(void)
{
	FILE *fp1, *fp2;
    char inFile[MAX], outFile[MAX];
    char rev[8];
	int i, j;
	char * fullText = (char *) malloc(44), * string = (char *) malloc(44);
	const char *arr[strlen(fullText)];		//blocks are stored here
	
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
    
    fullText = readFile(inFile);
    printf("\n%s",fullText);
    
    putchar('\n');
    
    for (i = 0; i < strlen(fullText); i++) {
        for (j = 0; j < 8; j++) {
    		string[j] = (fullText[i] & (1 << j)) ? '1' : '0';
	    }
	    string[j]='\0';
		
		strrev(string);
	    arr[i] = string;
	    
	    printf("%s\n",arr[i]);
    }
			
	fclose(fp1);
    fclose(fp2);
	return 0;
}

char *readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';        

    return code;
}
