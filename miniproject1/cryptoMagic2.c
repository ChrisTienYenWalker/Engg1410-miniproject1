#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

int main(char *, char *[]);
char *read(char *);
int write(char *, char *, int[], int);
unsigned int HextoAscii(char, char);
int decrypt(char *, char *);
int encrypt(char *, char *);
int main(char *crypt, char *inputs[])
{
    char *stringFile;
    if (inputs[2] == NULL)
    {
        stringFile = inputs[1];
    }
    else
    {
        stringFile = inputs[2];
    }
    char *text = read(stringFile);
    switch (inputs[1][1])
    {
    case 'E':
        encrypt(text, stringFile);
        break;
    case 'e':
        encrypt(text, stringFile);
        break;
    case 'D':
        decrypt(text, stringFile);
        break;
    case 'd':
        decrypt(text, stringFile);
        break;
    default:
        encrypt(text, inputs[1]);
        break;
    }
}
int encrypt(char *text, char *stringFile)
{
    //  for(int i = 0; i < strlen(text); i++){
    //         printf("%c", text[i]);
    //     }
    // read from file
    int newtext[512];
    // printf("%s", text);
    int length = strlen(text);
    int newtextposition = 0;
    // printf("%d", length);
    for (int i = 0; i < length; i++)
    {
        // printf("%c", text[i]);
        if ((text[i] == '<' && text[i + 1] == 't' && text[i + 2] == 'a' && text[i + 3] == 'b' && text[i + 4] == '>' ))
        {
            newtext[newtextposition] = 'T';
            newtext[newtextposition + 1] = 'T';
            newtextposition += 2;
            i += 4;
        }
        if (text[i] == '\n')
        {
            newtext[newtextposition] = '\n';
            newtextposition += 1;
            i += 3;
            continue;
        }
        else
        {
            int outchar = text[i];
            outchar = outchar - 16;
            if (outchar < 32)
            {
                outchar = (outchar - 32) + 144;
            }
            // printf("%x, ", outchar);
            newtext[newtextposition] = outchar;
            newtextposition += 1;
        }
    }
    write(stringFile, "crp", newtext, newtextposition);

    return 0;
}

int decrypt(char *text, char *stringFile)
{
    int asciiArray[512];
    int asciiArrayCounter = 0;
    for (int i = 0; i < strlen(text); i += 2)
    {
        if (text[i] == '\n' || text[i] == '\r')
        {
            asciiArray[asciiArrayCounter] = '\n';
            asciiArrayCounter++;
            i++;
        }

        if (text[i] == 'T' && text[i + 1] == 'T')
        {
            asciiArray[asciiArrayCounter] = 9;
            asciiArrayCounter++;
            i += 2;
        }

        unsigned char outchar = HextoAscii(text[i], text[i + 1]);
        printf("%c%c, ", text[i], text[i + 1]);
        printf("%d, ", outchar);
        outchar += 16;
        if (outchar > 127)
        {
            outchar = (outchar - 144) + 32;
        }
        printf("%c\n", outchar);

        asciiArray[asciiArrayCounter] = outchar;
        // printf("%c, ", outchar);
        // printf("%c", outchar);
        if (i < (ceil(strlen(text)) - 1))
        {
            asciiArrayCounter++;
        }
    }
    write(stringFile, "txt", asciiArray, asciiArrayCounter);
    return 0;
}

unsigned int HextoAscii(char hex1, char hex2)
{

    unsigned int ascii = 0;
    int y = 0;
    int x;
    long base = 1;
    if (hex2 >= '0' && hex2 <= '9')
    {
        ascii += (hex2 - 48) * base;
        base *= 16;
    }
    else if (hex2 >= 'A' && hex2 <= 'F')
    {
        ascii += (hex2 - 55) * base;
        base *= 16;
    }
    else if (hex2 >= 'a' && hex2 <= 'f')
    {
        ascii += (hex2 - 87) * base;
        base *= 16;
    }

    if (hex1 >= '0' && hex1 <= '9')
    {
        ascii += (hex1 - 48) * base;
    }
    else if (hex1 >= 'A' && hex1 <= 'F')
    {
        ascii += (hex1 - 55) * base;
    }
    else if (hex1 >= 'a' && hex1 <= 'f')
    {
        ascii += (hex1 - 87) * base;
    }

    return ascii;
}

char *read(char *fileName)
{
    char *text;
    long numbytes;

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
        printf("error");

    fseek(file, 0L, SEEK_END);
    numbytes = ftell(file);
    fseek(file, 0L, SEEK_SET);

    text = (char *)calloc(numbytes, sizeof(char));
    if (text == NULL)
        printf("error");

    fread(text, sizeof(char), numbytes, file);
    fclose(file);

    // printf(text);
    return text;
}

int write(char *fileName, char *filetype, int exportText[], int arraylength)
{
    FILE *fptr;
    fileName[strlen(fileName) - 3] = '\0';
    strcat(fileName, filetype);
    fptr = fopen(fileName, "w");
    if (!strcmp(filetype, "crp"))
    {
        for (int i = 0; i < arraylength; i++)
        {
            printf("%d", exportText[i]);
            if (exportText[i] == 'T' && exportText[i + 1] == 'T')
            {

                printf("tab insert");
                fprintf(fptr, "%c", exportText[i]);
                fprintf(fptr, "%c", exportText[i + 1]);
                i++;
            }
            if (exportText[i] == '\n')
            {
                fprintf(fptr, "\n");
                i += 3;
            }
            else
            {
                fprintf(fptr, "%x", exportText[i]);
            }
        }
    }
    else
    {
        // printf("hi");
        for (int i = 0; i < arraylength; i++)
        {
            // printf("%d", exportText[i]);
            fprintf(fptr, "%c", exportText[i]);
        }
    }
    fclose(fptr);

    return 0;
}
