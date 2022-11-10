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
    // printf("%s", stringFile);
    //  decryption
    if (!strcmp(inputs[1], "-D") || !strcmp(inputs[1], "-d"))
    {
        char *text;
        int asciiArray[126];
        text = read(stringFile);
        for (int i = 0; i < strlen(text) / 2; i++)
        {

            //avoiding unwanted characters
            if (text[i * 2] == ' ')
            {
                i++;
            }
            if(text[i * 2] == 'T' && text[i * 2 + 1] == 'T' ){
                i+=2;
            }
            if(text[i * 2] == '<' && text[i * 2 + 1] == 'C' && text[i * 2 + 2] == 'R' && text[i * 2 + 3] == '>'){
                i+=4;
            }
            asciiArray[i] = toHexAscii(text[i * 2], text[i * 2 + 1]);
            printf("%d", asciiArray[i]);
        }
    }
    // encryption
    else
    {
        char *text;
        // read from file
        text = read(stringFile);
        char newtext[256];
        // printf("%s", text);
        int length = strlen(text);
        int newtextposition = 0;
        // printf("%d", length);
        for (int i = 0; i < length; i++)
        {
            // printf("%c", text[i]);
            if (text[i] == '<')
            {
                char textSubString[6] = "";
                if (text[i + 1] == 't')
                {
                    memset(textSubString, '\0', 5);
                    strncpy(textSubString, text + i, 5);
                    // textSubString[5] = '\0';
                    // printf("%s", textSubString);
                    if (!strcmp(textSubString, "<tab>"))
                    {
                        newtext[newtextposition] = 'T';
                        newtext[newtextposition + 1] = 'T';
                        newtextposition += 2;
                        i += 4;
                        continue;
                    }
                    // printf("%d", length);
                }
                if (text[i + 1] == 'C')
                {
                    memset(textSubString, '\0', 4);
                    strncpy(textSubString, text + i, 4);
                    // textSubString[5] = '\0';
                    // printf("%s", textSubString);
                    if (!strcmp(textSubString, "<CR>"))
                    {
                        newtext[newtextposition] = '<';
                        newtext[newtextposition + 1] = 'C';
                        newtext[newtextposition + 2] = 'R';
                        newtext[newtextposition + 3] = '>';
                        newtextposition += 4;
                        i += 3;
                        continue;
                    }
                }
            }
            else
            {
                // printf("%d", i);
                // int outchar = text[i];
                // printf("%c", outchar);
                // outchar = outchar - 16;
                // if(outchar< 32){
                //     outchar = outchar-32 +144;
                // }
                newtext[newtextposition] = text[i];
                newtextposition += 1;
            }
        }

        // idea have an array in decimal and feed it into the write
        //  printf("%s", newtext);
        //  strcat( newtext, "hello");

        // write to file
        for (int i = 0; i < strlen(stringFile); i++)
        {
            if (stringFile[i] == '.')
            {
                // printf("deleted\n");
                stringFile[strlen(stringFile) - 3] = '\0';
                // printf("%s", stringFile);
                break;
            }
        }
        write(stringFile, "crp", newtext, newtextposition);
    }
    // printf("%s", inputs[1]);
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

    fseek(txtfile, 0L, SEEK_END);
    bytes = ftell(txtfile);
    fseek(txtfile, 0L, SEEK_SET);

    text = (char *)calloc(bytes, sizeof(char));

    if (text == NULL || text == 0)
    {
        printf("File Empty");
    }

    fread(text, sizeof(char), bytes, txtfile);

    // printf(text);
    fclose(txtfile);
    return text;
}

int write(char *fileName, char *filetype, char exportText[], int arraylength)
{
    FILE *txtfile;

    strcat(fileName, filetype);
    char *newFileName = fileName;
    FILE *newFILE;

    newFILE = fopen(newFileName, "w");
    // printf("%d", arraylength);
    if (!strcmp(filetype, "crp"))
    {
        for (int i = 0; i < arraylength; i++)
        {
            printf("%c", exportText[i]);
            if (exportText[i] == 'T' && exportText[i + 1] == 'T')
            {

                printf("tab insert");
                fprintf(newFILE, "%c", exportText[i]);
                fprintf(newFILE, "%c", exportText[i + 1]);
                i++;
            }
            else if (exportText[i] == '<' && exportText[i + 1] == 'C' && exportText[i + 2] == 'R' && exportText[i + 3] == '>')
            {
                fprintf(newFILE, "%c", exportText[i]);
                fprintf(newFILE, "%c", exportText[i + 1]);
                fprintf(newFILE, "%c", exportText[i + 2]);
                fprintf(newFILE, "%c\n", exportText[i + 3]);
                i += 3;
            }
            else
            {
                fprintf(newFILE, "%x", exportText[i]);
            }
        }
    }
    else
    {
        fprintf(newFILE, "%s", exportText);
    }
    fclose(newFILE);
    fileName[strlen(fileName) - 3] = '\0';

    return 0;
}
