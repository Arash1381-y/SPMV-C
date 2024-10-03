#include "matrix_mult_baseline.h"
#include <stdio.h>

void mult_baseline(matrix *m, vec *v, vec *r) {
  if (v->len != m->n_cols || r->len != m->n_rows) {
    printf("INVALID OPERATION!");
    return;
  }

  size_t row_num = m->n_rows;
  size_t col_num = m->n_cols;

  for (size_t i = 0; i < row_num; i++) {
    // mult this row of matrix to the vector
    // first entry of matrix row is : col_num * i and the end is col col_num *
    // (i+1) -1
    fflush(stdout);
    r->val[i] = 0;
    for (size_t j = 0; j < col_num; j++) {
      r->val[i] += m->flatt_val[i * col_num + j] * v->val[j];
    }
  }
}
