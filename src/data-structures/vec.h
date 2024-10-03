#ifndef C_SPMV_VEC_H
#define C_SPMV_VEC_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    size_t len;
    double *val;
} vec;


void init_vec(
        vec *v,
        size_t len,
        bool random_init,
        double sparsity
);


void print_vec(
        vec *v
);

void free_vec(
        vec *v
);

short is_equal(vec* v1, vec*v2);

#endif //C_SPMV_VEC_H
