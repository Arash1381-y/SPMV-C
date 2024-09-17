#include "./../utils/spmv_rand_gen.h"
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

size_t count_initial_zeros(const double arr[], size_t size);

void init_matrix(
        matrix *m,
        size_t row,
        size_t col,
        bool random_init,
        double sparsity
) {
    m->n_rows = row;
    m->n_cols = col;
    m->flatt_val = malloc(row * col * sizeof(double));

    if (!random_init) return;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double rand_value = simple_rand();
            if (rand_value < sparsity) {
                m->flatt_val[i * col + j] = 0;
            } else {
                m->flatt_val[i * col + j] = rand_gen_m_entry();
            }
        }
    }
}

void print_matrix(
        matrix *m
) {
    for (int i = 0; i < m->n_rows; i++) {
        for (int j = 0; j < m->n_cols; j++) {
            printf("%f, ", m->flatt_val[i * m->n_cols + j]);
        }
        printf("\n");
    }
}

void init_sparse_csr(
        matrix *m,
        sparse_CSR *s
) {
    size_t n_rows, n_cols;
    n_rows = s->n_rows = m->n_rows;
    n_cols = s->n_cols = m->n_cols;

    size_t non_zeros = n_rows * n_cols - count_initial_zeros(m->flatt_val, s->n_cols * s->n_rows);
    s->n_nz = non_zeros;

    s->row_ptrs = malloc(sizeof(size_t) * (s->n_rows + 1));
    s->col_indices = malloc(sizeof(size_t) * non_zeros);
    s->flatt_val = malloc(sizeof(double) * non_zeros);

    double *flatt_val_m = m->flatt_val;

    size_t nz_id = 0;
    for (size_t i = 0; i < n_rows; i++) {
        s->row_ptrs[i] = nz_id;
        for (size_t j = 0; j < n_cols; j++) {
            if (flatt_val_m[i * n_cols + j] != 0) {
                s->col_indices[nz_id] = j;
                s->flatt_val[nz_id] = flatt_val_m[i * n_cols + j];
                nz_id++;
            }
        }
    }
    s->row_ptrs[n_rows] = nz_id;
}

void print_sparse_scr(sparse_CSR *s) {
    printf("row\tcol\tval\n");
    printf("---\n");
    for (size_t i = 0; i < s->n_rows; i++) {
        size_t nz_start = s->row_ptrs[i];
        size_t nz_end = s->row_ptrs[i + 1];
        for (size_t nz_id = nz_start; nz_id < nz_end; nz_id++) {
            size_t j = s->col_indices[nz_id];
            double val = s->flatt_val[nz_id];
            printf("%zu\t%zu\t%f\n", i, j, val);
        }
    }
}


size_t count_initial_zeros(const double arr[], size_t size) {
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == 0)
            count++;
    }
    return count;
}


void free_matrix(matrix *m) {
    free(m->flatt_val);
}

void free_sparse_csr(sparse_CSR *s) {
    free(s->row_ptrs);
    free(s->col_indices);
    free(s->flatt_val);
}

