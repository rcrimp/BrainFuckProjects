#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 1024
static char tape[ARR_LEN] = {0};

int charType(char c){
   switch (c){
      case '>': return 1; 
      case '<': return 1;
      case '+': return 1;
      case '-': return 1;
      case '.': return 1;
      case ',': return 1;
      case '[': return 1;
      case ']': return 1;
   }
   return 0;
}

int fileToArray(FILE *f, char **array, int* size){
   *array = malloc(512 * sizeof(char));
   int c, n = 0;
   while ((c = fgetc(f)) != EOF){
      if (1 == charType((char)c)){
         (*array)[n++] = (char)c;
      }
   }
   (*array)[n] = '\0';
   *size = n;
   return 0;
}

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

   /* read file into source array */
   char *source = NULL;
   fileToArray(file, &source, &count); 

   /* interpreter */
   ptr = tape;
   int c;
   for(i = 0; i < count; i++){ 
      switch(source[i]){
         case '>': ptr++; break;
         case '<': ptr--; break;
         case '+': (*ptr)++; break;
         case '-': (*ptr)--; break;
         case '.': putchar(*ptr); break;
         case ',': *ptr=getchar(); break;
         case '[': /* while(*ptr){ */ 
                   if (0 == *ptr) { /* jump forward to matching ']' */
                      i++; /* skip the '[' */
                      int bc = 1;
                      while(bc != 0){
                        if (source[i] == '[') bc++;
                        if (source[i] == ']') bc--;
                        i++;
                      }
                   }
                   break;
         case ']': 
                   if (0 != *ptr){ /* jump backward to matching '[' */
                     i--;
                     int bc = 1;
                     while (bc != 0){
                        if (source[i] == ']') bc++;
                        if (source[i] == '[') bc--;
                        i--;
                     }
                   }
                   break;
      }
   }

   fclose(file);
   return 0;
}
