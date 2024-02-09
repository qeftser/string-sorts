
#include "sorts.h"

#define swap(A,B) char *temp = A; A = B; B = temp


/* A = array to sort
 * i = radix to sort at
 * m = length of A
 */
void counting_sort(char *A[], int i, int m) {
   static unsigned int C[256];
   /* allocate to heap to avoid overflowing stack */
   char **B = malloc(sizeof(char *)*m);
   int j;
   /* initialize C */
   for (j = 0; j+3 < 256; j+=4) {
      C[j] = 0;
      C[j+1] = 0;
      C[j+2] = 0;
      C[j+3] = 0;
   }
   /* count */
   for (j = 0; j < m; j++) {
      C[*(A[j]+i)]++;
   }
   /* incriment */
   for (j = 1; j < 256; j++) {
      C[j] += C[j-1];
   }
   /* 'sort' */
   for (j = m-1; j >= 0; j--) {
      B[C[*(A[j]+i)]-1] = A[j];
      C[*(A[j]+i)]--;
   }
   /* copy results of B to A. They are all pointers so it is fine */
   for (j = 0; j < m; j++) {
      A[j] = B[j];
   }
}

int pivot(char *a[], int l, int r, int d) {
   return a[(l+r)/2][d];
}

/* A = array
 * l = lower index - I used p for the pivot
 * r = upper index
 * d = current radix
 * p = pivot
 * i = end index for values lower than pivot
 * j = end index for values greater than pivor
 *
 * Partition returns two values, so after this the lower values are
 * between l and i, the higher values are between j and r, and the
 * values equal to the pivot are between i and j */
void three_way_radix_partition(char *a[], int l, int r, int d, int p, int *i, int *j) {
   r--; /* exclude high value */
   int lo,hi,eq;
   lo = l; 
   eq = l;
   hi = r;
   while (eq <= hi) {
      if (a[eq][d] < p) {
         swap(a[eq],a[lo]);
         lo++;
         eq++;
      }
      else if (a[eq][d] > p) {
         swap(a[eq],a[hi]);
         hi--;
      }
      else {
         eq++;
      }
   }
   *i = lo;
   *j = hi;
}

///////////////////////////////////////////////////
///  Sorts 
///////////////////////////////////////////////////

/* A = array to sort
 * n = length of inputs (how many radixes?)
 * m = length of array */
void radix_counting_sort(char *A[], int m, int n) {
   for (int i = n-1; i >= 0; i--) {
      counting_sort(A, i, m);
   }
}

/* A = array to sort
 * l = lower index bound
 * r = upper index bound
 * d = current radix
 * n = length of inputs (total radix count) */
void three_way_radix_quicksort(char *a[], int l, int r, int d, int n) {
   int i, j, p;
   if ((r-l) <= 1 || d > n) return;
   p = pivot(a, l, r, d);
   three_way_radix_partition(a,l,r,d,p,&i,&j);
   three_way_radix_quicksort(a,l,i,d,n);
   three_way_radix_quicksort(a,i,j,d+1,n);
   three_way_radix_quicksort(a,j,r,d,n);
}

