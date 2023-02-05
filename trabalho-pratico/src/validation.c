#include "validation.h"

void compareFiles(FILE *fp1, FILE *fp2){
   // fetching character of two file
   // in two variable ch1 and ch2
   char ch1 = getc(fp1);
   char ch2 = getc(fp2);
  
   // error keeps track of number of errors
   // pos keeps track of position of errors
   // line keeps track of error line
   int error = 0, pos = 0, line = 1;
  
   // iterate loop till end of file
   while (ch1 != EOF && ch2 != EOF){
      pos++;
  
      // if both variable encounters new
      // line then line variable is incremented
      // and pos variable is set to 0
      if (ch1 == '\n' && ch2 == '\n')
      {
         line++;
         pos = 0;
      }
  
      // if fetched data is not equal then
      // error is incremented
      if (ch1 != ch2)
      {
         error++;
         printf("Line Number : %d \tError"
            " Position : %d \n", line, pos);
      }
  
      // fetching character until end of file
      ch1 = getc(fp1);
      ch2 = getc(fp2);
   }
  
   printf("Total Errors: %d\n", error);
}

int validaQueriesB(int linha,char *path,char *commands){
   char comando[1024];
   int maxlen = sizeof comando;
   snprintf(comando,maxlen, "%sResultados/command%d_output.txt",path,linha);
   
   char comando2[1024];
   int maxlen2 = sizeof comando2;
   snprintf(comando2,maxlen2, "%scommand%d_output.txt",commands,linha);
   
   FILE *file1 = fopen(comando, "r");
   FILE *file2 = fopen(comando2, "r");
   if (file1 == NULL || file2 == NULL){
      printf("Error: Files not open");
      exit(0);
   }

   printf("-------------------------- Query %d: --------------------------- \n",linha);
   compareFiles(file1, file2);
   fclose(file1);
   fclose(file2);
   return 0;
}
