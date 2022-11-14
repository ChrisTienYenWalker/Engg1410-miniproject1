#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

int main(char *, char *[]);
char *read(char *);
int write(char *, char *, int [], int);
int toHexAscii(char, char);

int main(char *crypt, char *inputs[])
{
    char *stringFile;
    if(inputs[2] == NULL){
        stringFile = inputs[1];
    }else{
        stringFile = inputs[2];
    }
    char *text;
    text = read(stringFile);
    printf("%s", stringFile);

    int asciiArray[256];
    int asciiArrayCounter = 0;
    for(int i = 0; i < strlen(text)/2; i++){
        if(text[i] == 'T' && text[i+1] == 'T'){
            asciiArray[asciiArrayCounter] = 9;
            asciiArrayCounter++;
            i++;
        }
        if(text[i*2] == '<' && text[i*2+1] == 'C' && text[i*2+2] == 'R' && text[i*2+3] == '>'){
            asciiArray[asciiArrayCounter] = 60;
            asciiArray[asciiArrayCounter+1] = 67;
            asciiArray[asciiArrayCounter+2] = 82;
            asciiArray[asciiArrayCounter+3] = 62;
            asciiArrayCounter+=4;
            i+=2;
        }
        else{
            char outchar = toHexAscii(text[i*2], text[i*2+1]);
            printf("\n%c, %c, ", text[i*2], text[i*2+1]);
            printf("%d", outchar);
            outchar += 16;
            if(outchar > 127){
                outchar = outchar-144+32;
            }
            asciiArray[asciiArrayCounter] = outchar;
            asciiArrayCounter++;
        }
    }
    write(stringFile, "txt", asciiArray, asciiArrayCounter);
}

int toHexAscii(char hex1, char hex2)
{
    int ascii = 0;
    int y = 0;
    int x, i;
    if (hex2 >= '0' && hex2 <= '9')
    {
        x = hex2 - '0';
    }
    else
    {
        x = hex2 - 'A' + 10;
    }
    ascii = ascii + x * pow(16, y++); // converting hexadecimal to integer value ++y;
    if (hex1 >= '0' && hex1 <= '9')
    {
        x = hex1 - '0';
    }
    else
    {
        x = hex1 - 'A' + 10;
    }
    ascii = ascii + x * pow(16, y); // converting hexadecimal to integer value ++y;

return ascii;
}

char *read(char *fileName)
{
    FILE *txtfile;
    char *text = "";
    char newtext[256];
    long bytes;
    // open and read file
    txtfile = fopen(fileName, "r");

    if (txtfile == NULL)
    {
        printf("File Empty");
    }

    text = (char *)calloc(bytes, sizeof(char));

    if (text == NULL || text == 0)
    {
        printf("File Empty");
    }
    while(fgets(newtext,sizeof newtext,txtfile)!= NULL) /* read a line from a file */ {
        strcat(text, newtext);
    }
    // fread(text, sizeof(char), bytes, txtfile);

    fclose(txtfile);
    return text;
}

int write(char *fileName, char *filetype, int exportText[], int arraylength)
{
    FILE *fptr;
    fileName[strlen(fileName)-3] = '\0';
    strcat(fileName, filetype);

    fptr = fopen(fileName,"w");
    if(!strcmp(filetype, "crp")){
        for (int i = 0; i < arraylength; i++)
        {
            printf("%c", exportText[i]);
            if (exportText[i] == 'T' && exportText[i + 1] == 'T')
            {

                printf("tab insert");
                fprintf(fptr, "%c", exportText[i]);
                fprintf(fptr, "%c", exportText[i + 1]);
                i++;
            }
            else if (exportText[i] == '<' && exportText[i + 1] == 'C' && exportText[i + 2] == 'R' && exportText[i + 3] == '>')
            {
                fprintf(fptr, "%c", exportText[i]);
                fprintf(fptr, "%c", exportText[i + 1]);
                fprintf(fptr, "%c", exportText[i + 2]);
                fprintf(fptr, "%c\n", exportText[i + 3]);
                i += 3;
            }
            else
            {
                fprintf(fptr, "%x", exportText[i]);
            }
        }
    }
    else{
        for(int i = 0; i < arraylength; i++){
            fprintf(fptr,"%c",exportText[i]);
        }
    }
    fclose(fptr);

    return 0;
}

