/* multiply vector components, write into a vector,
 *  and compute the inner product  */
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main (int argc, char **argv)
{
  long  i, n;
  double *a, *b, *c;
  double prod;
  long p, passes, skip;

  if (argc != 4) {
    fprintf(stderr, "Function needs vector size, number of passes and\n a number of elements to skip as input arguments!\n");
    abort();
  }

  n = atol(argv[1]);
  passes = atol(argv[2]);
  skip = atol(argv[3]);

  a = (double *) malloc(sizeof(double) * n);
  b = (double *) malloc(sizeof(double) * n);
  c = (double *) malloc(sizeof(double) * n);

  /* fill vectors */
  for (i = 0; i < n; ++i) {
    a[i] = i+1;
    b[i] = 2.0 / (i+1);
  }

  timestamp_type time1, time2;
  get_timestamp(&time1);

  for (p = 0; p < passes; ++p)
    {
      for (i = 0; i < n; i += skip) {
	c[i] = a[i] * b[i];
      }
      prod = 0.0;
      for (i = 0; i < n; i += skip) {
      	prod += c[i];
      }
    }

  get_timestamp(&time2);
  double elapsed = timestamp_diff_in_seconds(time1,time2);
  printf("Time elapsed is %f seconds.\n", elapsed);
  printf("Inner product is %f.\n", prod);

  printf("%f GB/s\n", 4*n*sizeof(double)*passes/1e9/elapsed/skip);
  printf("%f GFlops/s\n", 2*n*passes/1e9/elapsed/skip);

  free(a);
  free(b);
  free(c);
  return 0;
}
