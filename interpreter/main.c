#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 1024
static char tape[ARR_LEN] = {0};

int main(int argc, char*argv[]){
   FILE *file;
   int i, count; 
   char *ptr;

   /* ensure there is 1 argument */
   if (argc != 2){
      fprintf(stderr, "Please provide the source file as an argument\n");
      return 1;
   }

   /* attempt to open the source file */
   if (!(file = fopen(argv[1], "rt"))){
      fprintf(stderr, "Unable to open the file: %s\n", argv[1]);
      return 1;
   }

   /* interpreter TODO add loops */
   ptr = tape;
   int c;
   while ((c = fgetc(file)) != EOF){ 
      switch(c){
         case '>': ptr++; break;
         case '<': ptr--; break;
         case '+': (*ptr)++; break;
         case '-': (*ptr)--; break;
         case '.': putchar(*ptr); break;
         case ',': *ptr=getchar(); break;
         case '[': /* while(*ptr){ */ break;
         case ']': /* } */ break;
      }
   }

   fclose(file);
   return 0;
}
