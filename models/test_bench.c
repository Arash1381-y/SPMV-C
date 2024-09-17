#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../data-structure/matrix.h"
#include "../data-structure/vec.h"
#include "./vectorize/matrix_mult_CSR_vectorize.h"
#include "./baseline/matrix_mult_baseline.h"
#include "./sparse-singlethread/matrix_mult_CSR_single_thread.h"
#include "./sparse-multithread/matrix_mult_CSR_multi_thread.h"

#include <stdio.h>

int main() {
    srand(time(NULL));  // Seed the random number generator with the current time
    size_t row, col;
    row = 10000;
    col = 10000;
    double sparsity = 0.75;

    matrix *m = malloc(sizeof(matrix));
    init_matrix(m, row, col, true, sparsity);
    //printf("matrix: \n");
    //print_matrix(m);

    //printf("vector: \n");
    vec *v = malloc(sizeof(vec));
    init_vec(v, col, true, 0);
    //print_vec(v);

    vec *baseline_result = malloc(sizeof(vec));
    init_vec(baseline_result, row, false, sparsity);

    vec *st_result = malloc(sizeof(vec));
    init_vec(st_result, row, false, sparsity);

    vec *mt_result = malloc(sizeof(vec));
    init_vec(mt_result, row, false, sparsity);

    vec *vectorize_result = malloc(sizeof(vec));
    init_vec(vectorize_result, row, false, sparsity);

    clock_t start, end;
    double elapsed_time_baseline, elapsed_time_st, elapsed_time_mt, elapsed_time_vectorize, elapsed_time_csr;

    // Measure the time taken by the baseline multiplication
    start = clock();
    mult_baseline(m, v, baseline_result);
    end = clock();
    elapsed_time_baseline = ((double) (end - start)) / CLOCKS_PER_SEC;

    // create sparse matrix and measure the time taken to convert the matrix to sparse CSR format
    start = clock();
    sparse_CSR *s = malloc(sizeof(sparse_CSR));
    init_sparse_csr(m, s);
    end = clock();
    elapsed_time_csr = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Measure the time taken by the sparse CSR multiplication with 4 threads
    start = clock();
    mult_csr_multi_thread(s, v, mt_result);
    end = clock();
    elapsed_time_mt = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Measure the time taken by the sparse CSR multiplication with 1 thread
    start = clock();
    mult_csr_single_thread(s, v, st_result);
    end = clock();
    elapsed_time_st = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Measure the time taken by the vectorized sparse CSR multiplication with 1 thread
    start = clock();
    mult_csr_vectorize(s, v, vectorize_result);
    end = clock();
    elapsed_time_vectorize = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("REPORT OF SPARSE MATRIX MULTIPLICATION WITH %zu ROWS AND %zu COLUMNS AND SPARSITY OF %f\n", row, col,
           sparsity);

    printf("________________________________________________________________________\n");
    printf("|    Method     | Time taken (s) | Speedup  | Efficiency | Correctness |\n");
    printf("|---------------|----------------|----------|------------|-------------|\n");
    printf("|   Baseline    | %.3f          |     1    |    1       | %s        |\n", elapsed_time_baseline,
           is_equal(baseline_result, st_result) ? "true" : "false");
    printf("|---------------|----------------|----------|------------|-------------|\n");
    printf("| Single thread | %.3f          |  %.3f   |  %.3f     | %s        |\n", elapsed_time_st,
           elapsed_time_baseline / elapsed_time_st,
           (elapsed_time_baseline / elapsed_time_st) / 1, is_equal(baseline_result, st_result) ? "true" : "false");
    printf("|---------------|----------------|----------|------------|-------------|\n");
    printf("|  Multi thread | %.3f          |  %.3f   |  %.3f     | %s        |\n", elapsed_time_mt,
           elapsed_time_baseline / elapsed_time_mt,
           (elapsed_time_baseline / elapsed_time_mt) / 4, is_equal(baseline_result, mt_result) ? "true" : "false");
    printf("|---------------|----------------|----------|------------|-------------|\n");
    printf("|   Vectorized  | %.3f          |  %.3f   |  %.3f     | %s        |\n", elapsed_time_vectorize,
           elapsed_time_baseline / elapsed_time_vectorize,
           (elapsed_time_baseline / elapsed_time_vectorize) / 1,
           is_equal(baseline_result, vectorize_result) ? "true" : "false");
    printf("|---------------|----------------|----------|------------|-------------|\n");
    printf("|       CSR     |  %.3f         | %.3f    | %.3f      | %s        |\n", elapsed_time_csr,
           elapsed_time_baseline / elapsed_time_csr,
           (elapsed_time_baseline / elapsed_time_csr) / 1, is_equal(baseline_result, st_result) ? "true" : "false");
    printf("|---------------|----------------|----------|------------|-------------|\n");

    free_matrix(m);
    free_vec(v);
    free_vec(baseline_result);
    free_vec(st_result);
    free_vec(mt_result);
    free_vec(vectorize_result);
    free_sparse_csr(s);
    return 0;
}