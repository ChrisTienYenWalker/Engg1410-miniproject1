#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

int main(char *, char *[]);
char *read(char *);
int write(char *, char *, char[], int);
int toHexAscii(char, char);

int main(char *crypt, char *inputs[])
{
    char *stringFile = inputs[2];
    char text;
    text = read(stringFile);
    printf("%s", text);

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
    char *text;
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

    fread(text, sizeof(char), bytes, txtfile);

    fclose(txtfile);
    return text;
}

int write(char *fileName, char *filetype, char exportText[], int arraylength)
{
    FILE *fptr;
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
        fprintf(fptr,"%s",exportText);
    }
    fclose(fptr);

    return 0;
}

