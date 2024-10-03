//
// Created by halfblood on 7/5/23.
//

#ifndef C_SPMV_MATRIX_H
#define C_SPMV_MATRIX_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct matrix {
    size_t n_rows;
    size_t n_cols;
    double *flatt_val;
} matrix;


typedef struct sparse_CSR {
    size_t n_rows;
    size_t n_cols;
    size_t n_nz;
    size_t *row_ptrs;
    size_t *col_indices;
    double *flatt_val;
} sparse_CSR;

void init_matrix(
        matrix *m,
        size_t row,
        size_t col,
        bool random_init,
        double sparsity
);

void init_sparse_csr(
        matrix *m,
        sparse_CSR *s
);

void print_matrix(
        matrix *m
);

void print_sparse_scr(sparse_CSR *s);

void free_matrix(matrix *m);

void free_sparse_csr(sparse_CSR *s);


#endif //C_SPMV_MATRIX_H
