#ifndef C_SPMV_MATRIX_MULT_CSR_MULTI_THREAD_H
#define C_SPMV_MATRIX_MULT_CSR_MULTI_THREAD_H

#include "matrix.h"
#include "vec.h"

void mult_csr_multi_thread(sparse_CSR *s, vec *v, vec *r);

#endif
