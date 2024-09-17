#ifndef C_SPMV_MATRIX_MULT_CSR_MULTI_THREAD_H
#define C_SPMV_MATRIX_MULT_CSR_MULTI_THREAD_H

#include "../../data-structure/vec.h"
#include "../../data-structure/matrix.h"

void mult_csr_multi_thread(sparse_CSR *s, vec *v, vec *r);

#endif
