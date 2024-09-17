//
// Created by halfblood on 7/6/23.
//

#ifndef C_SPMV_MATRIX_MULT_CSR_VECTORIZE_H
#define C_SPMV_MATRIX_MULT_CSR_VECTORIZE_H


#include "../../data-structure/matrix.h"
#include "../../data-structure/vec.h"

void mult_csr_vectorize(sparse_CSR *s, vec *v, vec *r);

#endif //C_SPMV_MATRIX_MULT_CSR_VECTORIZE_H
