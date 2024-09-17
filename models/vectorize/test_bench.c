#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../../data-structure/matrix.h"
#include "../../data-structure/vec.h"
#include "matrix_mult_CSR_vectorize.h"
#include "../baseline/matrix_mult_baseline.h"
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

    vec *r1 = malloc(sizeof(vec));
    init_vec(r1, row, false, sparsity);

    clock_t start, end;
    double elapsed_time;

    // Measure the time taken by the baseline multiplication
    start = clock();
    mult_baseline(m, v, r1);
    end = clock();
    elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Baseline multiplication time: %f seconds\n", elapsed_time);
    //print_vec(r);

    sparse_CSR *s = malloc(sizeof(sparse_CSR));

    // Measure the time taken to convert the matrix to sparse CSR format
    start = clock();
    init_sparse_csr(m, s);
    end = clock();
    double elapsed_time1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sparse CSR conversion time: %f seconds\n", elapsed_time1);
    //print_sparse_scr(s);

    vec *r2 = malloc(sizeof(vec));
    init_vec(r2, row, false, sparsity);

    // Measure the time taken by the sparse CSR multiplication
    start = clock();
    mult_csr_vectorize(s, v, r2);
    end = clock();


    double elapsed_time2 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sparse CSR multiplication time: %f seconds\n", elapsed_time2);
    printf("total CSR time: %f seconds\n", elapsed_time1 + elapsed_time2);
    //print_vec(r);

    if (!is_equal(r1, r2)) {
        printf("WRONG COMPUTATION!!!\n");
    }

    free_matrix(m);
    free_vec(v);
    free_vec(r1);
    free_sparse_csr(s);

    return 0;
}