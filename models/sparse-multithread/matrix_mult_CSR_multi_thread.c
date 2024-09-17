#include <stdio.h>
#include "matrix_mult_CSR_multi_thread.h"

void mult_csr_multi_thread(sparse_CSR *s, vec *v, vec *r) {
    if (v->len != s->n_cols || r->len != s->n_rows) {
        printf("INVALID OPERATION!");
    }


    size_t temp[s->n_rows][2];
    double temp_r[s->n_rows][1];
#pragma omp parallel for num_threads(8)
    for (size_t i = 0; i < s->n_rows; i++) {
        temp[i][0] = s->row_ptrs[i];
        temp[i][1] = s->row_ptrs[i + 1];
        temp_r[i][0] = 0;
    }


    double *v_temp;
    v_temp = v->val;

#pragma omp parallel for firstprivate(v_temp)  num_threads(4) schedule(dynamic, 80)
    for (size_t i = 0; i < s->n_rows; i++) {
        size_t nz_start = temp[i][0];
        size_t nz_end = temp[i][1];

        for (size_t nz_id = nz_start; nz_id < nz_end; nz_id++) {
            size_t j = s->col_indices[nz_id];
            double val = s->flatt_val[nz_id];

            temp_r[i][0] = temp_r[i][0] + val * v_temp[j];
        }
    }

#pragma omp parallel
    for (size_t i = 0; i < s->n_rows; i++) {
        r->val[i] = temp_r[i][0];
    }
}
