#include <stdio.h>
#include "matrix_mult_CSR_vectorize.h"
#include <immintrin.h>

void mult_csr_vectorize(sparse_CSR *s, vec *v, vec *r) {
    if (v->len != s->n_cols || r->len != s->n_rows) {
        printf("INVALID OPERATION!");
    }

    for (size_t i = 0; i < s->n_rows; i++) {
        r->val[i] = 0;
        size_t nz_start = s->row_ptrs[i];
        size_t nz_end = s->row_ptrs[i + 1];


        // iterate through the elements in the row
        for (size_t nz_id = nz_start; nz_id < nz_end;) {
            size_t num_elements_left = nz_end - nz_id - 1;
            if (num_elements_left < 4) {
                // if there are less than 4 elements left, do the normal multiplication
                r->val[i] = r->val[i] + s->flatt_val[nz_id] * v->val[s->col_indices[nz_id]];
                nz_id++; // increment nz_id
            } else {
                __m256d val = {s->flatt_val[nz_id], s->flatt_val[nz_id + 1],
                               s->flatt_val[nz_id + 2], s->flatt_val[nz_id + 3]};
                // load the 4 corresponding elements from the vector
                __m256d vec = {v->val[s->col_indices[nz_id]], v->val[s->col_indices[nz_id + 1]],
                               v->val[s->col_indices[nz_id + 2]], v->val[s->col_indices[nz_id + 3]]};
                // do the mult
                __m256d mult = _mm256_mul_pd(val, vec);

                // unpack the result
                double *mult_unwrapped = (double *) &mult;
                // add the result to the sum
                r->val[i] = r->val[i] + mult_unwrapped[0] + mult_unwrapped[1] + mult_unwrapped[2] + mult_unwrapped[3];
                nz_id += 4; // increment nz_id
            }
        }
    }
}
