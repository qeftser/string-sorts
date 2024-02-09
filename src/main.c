
#include "sorts.h"
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {

   if (argc < 2) {
      printf("usage: string-sorts <file-name>\n");
      exit(1);
   }

   char *file_path = argv[1];

   FILE *fptr = fopen(file_path,"r");
   if (fptr == NULL) {
      printf("unable to open file\n"); exit(1);
   }

   /* This first segment determines the total words and longest word.
    * Both of these values are important to the sorts, so it is nessesary
    * to collect them */
   char c[80];
   int words = 0;
   int longest_len = 0;
   double avg_len = 0;
   while (fscanf(fptr, " %s",c) == 1) {
      words++;
      int curr_len = strlen(c);
      avg_len += curr_len;
      if (curr_len > longest_len) {
         longest_len = curr_len;
      }
   }
   avg_len /= (double) words;

   char *A[words];
   char *Reset[words];

   /* would have done a fseek but it is easier to scan strings this way */
   fclose(fptr);
   fptr = fopen(file_path,"r");

   /* This block reads in strings and saves pointers to them to the array A
    * I chose to allocate to the heap here because it is larger and allocating to
    * the stack would require me to know the highest string length before hand and
    * I wanted to decide that in the program. So yeah it is a little slower but
    * I think it was a good idea */
   int i, j = 0;
   while (fscanf(fptr," %s",c) == 1) {
      i = 0;
      A[j] = malloc(sizeof(char)*(longest_len+1)); /* +1 for '\0' */
      while (c[i] != '\0') {
         A[j][i] = c[i];
         i++;
      }
      while (i < longest_len) {
         A[j][i++] = 3; /* three is the ETX character, which will be less than all other
                           characters that appear in the text */
      }
      A[j][longest_len] = '\0';
      j++;
   }

   fclose(fptr);

   /* Reset is here to reset A after sorting */
   for (i = 0; i < words; i++) {
      Reset[i] = A[i];
   }

   printf("total words:      %d\n",words);
   printf("average word len: %.2f\n",avg_len);
   printf("longest word len: %d\n\n",longest_len);

   clock_t tStart;

   printf("sorting with radix_counting_sort\n");
   tStart = clock();
   radix_counting_sort(A, words, longest_len);
   printf("time elapsed: %f\n\n", (double) tStart / CLOCKS_PER_SEC);

   /* reset A */
   for (i = 0; i < words; i++) {
      A[i] = Reset[i];
   }

   printf("sorting with three_way_radix_quicksort\n");
   tStart = clock();
   three_way_radix_quicksort(A,0,words,0,longest_len);
   printf("time elapsed: %f\n\n", (double) tStart / CLOCKS_PER_SEC);

   /* reset A */
   for (i = 0; i < words; i++) {
      A[i] = Reset[i];
   }


   return 0;
}
