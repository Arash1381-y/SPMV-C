#ifndef C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H
#define C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H

#include "matrix.h"
#include "vec.h"

void mult_csr_single_thread(sparse_CSR *s, vec *v, vec *r);
#endif // C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H
