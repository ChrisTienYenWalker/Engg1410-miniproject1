#include <stdio.h>
#include <stdlib.h>

int main()
{
   int num;
   FILE *fptr;

   if ((fptr = fopen("something.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
    while(!feof(fptr)){
        fscanf(fptr,"%d,", &num);
        printf("%c", num);
    }

   fclose(fptr);

   return 0;
}
