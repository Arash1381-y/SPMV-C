#include "baseline/matrix_mult_baseline.h"
#include "matrix.h"
#include "sparse-singlethread/matrix_mult_CSR_single_thread.h"
#include "vec.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL)); // Seed the random number generator with the current time
  size_t row, col;
  row = 2;
  col = 2;
  double sparsity = 0.75;

  matrix *m = malloc(sizeof(matrix));
  init_matrix(m, row, col, true, sparsity);

#ifdef DEBUG
  printf("matrix: \n");
  print_matrix(m);
#endif

#ifdef DEBUG
  printf("vector: \n");
#endif
  vec *v = malloc(sizeof(vec));
  init_vec(v, col, true, 0);
#ifdef DEBUG
  print_vec(v);
#endif

  vec *r1 = malloc(sizeof(vec));
  init_vec(r1, row, false, sparsity);

#ifdef CHRONO
  clock_t start, end;
  double elapsed_time;
#endif

  // Measure the time taken by the baseline multiplication
#ifdef CHRONO
  start = clock();
#endif
  mult_baseline(m, v, r1);
#ifdef CHRONO
  end = clock();
  elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Baseline multiplication time: %f seconds\n", elapsed_time);
#endif

#ifdef DEBUG
  print_vec(r);
#endif

  sparse_CSR *s = malloc(sizeof(sparse_CSR));

  // Measure the time taken to convert the matrix to sparse CSR format
#ifdef CHRONO
  start = clock();
#endif

  init_sparse_csr(m, s);

#ifdef CHRONO
  end = clock();
  double elapsed_time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Sparse CSR conversion time: %f seconds\n", elapsed_time1);
#endif

#ifdef DEBUG
  // print_sparse_scr(s);
#endif

  vec *r2 = malloc(sizeof(vec));
  init_vec(r2, row, false, sparsity);

// Measure the time taken by the sparse CSR multiplication
#ifdef CHRONO
  start = clock();
#endif
  mult_csr_single_thread(s, v, r2);
#ifdef CHRONO
  end = clock();
  double elapsed_time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Sparse CSR multiplication time: %f seconds\n", elapsed_time2);
  printf("total CSR time: %f seconds\n", elapsed_time1 + elapsed_time2);
#endif

#ifdef DEBUG
  print_vec(r);
#endif

  assert(is_equal(r1, r2));

  free_matrix(m);
  free_vec(v);
  free_vec(r1);
  free_sparse_csr(s);

  printf("[SINGLE-THREAD] : TEST PASSED !\n");

  return 0;
}