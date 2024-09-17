#ifndef C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H
#define C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H

#include "../../data-structure/vec.h"
#include "../../data-structure/matrix.h"

void mult_csr_single_thread(sparse_CSR *s, vec *v, vec *r);
#endif //C_SPMV_MATRIX_MULT_CSR_SINGLE_THREAD_H
