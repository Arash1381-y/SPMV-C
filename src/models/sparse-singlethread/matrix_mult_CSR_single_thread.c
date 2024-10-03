#include <stdio.h>
#include "matrix_mult_CSR_single_thread.h"

void mult_csr_single_thread(sparse_CSR *s, vec *v, vec *r) {
    if (v->len != s->n_cols || r->len != s->n_rows) {
        printf("INVALID OPERATION!");
    }

    for (size_t i = 0; i < s->n_rows; i++) {
        r->val[i] = 0;
        size_t nz_start = s->row_ptrs[i];
        size_t nz_end = s->row_ptrs[i + 1];
        for (size_t nz_id = nz_start; nz_id < nz_end; nz_id++) {
            size_t j = s->col_indices[nz_id];
            double val = s->flatt_val[nz_id];
            r->val[i] = r->val[i] + val * v->val[j];
        }
    }
}
