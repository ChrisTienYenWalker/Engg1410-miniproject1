#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;

    char string[50];
    int i=0, c=1;

    fptr = fopen("C:\\asciiwritefile.txt","w");

    while (c==1){
        printf("Enter the Sentence: ");
        scanf("%s",string);
        while(string[i]!='\0') {
            fprintf(fptr,"%d,", string[i]);
            i++;
        }
        fprintf(fptr,"%d,",'\0');
        i=0;
        printf("Continue? (y=1, n=0): ");
        scanf(" %d",&c);
    }

    fclose(fptr);

return(0);
}
