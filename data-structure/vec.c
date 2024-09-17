#include <stdio.h>
#include "vec.h"
#include "./../utils/spmv_rand_gen.h"


void init_vec(
        vec *v,
        size_t len,
        bool random_init,
        double sparsity
) {
    v->len = len;
    v->val = malloc(len * sizeof(double));

    if (!random_init) return;

    for (int i = 0; i < len; i++) {
        double rand_value = simple_rand();
        if (rand_value < sparsity) {
            v->val[i] = 0;
        } else {
            v->val[i] = rand_gen_m_entry();
        }
    }
}

void print_vec(
        vec *v
) {
    for (int i = 0; i < v->len; i++) {
        printf("%f, ", v->val[i]);
    }
    printf("\n");
}

void free_vec(
        vec *v
) {
    free(v->val);
}

short is_equal(vec *v1, vec *v2) {
    size_t len = v1->len;
    if (v2->len != len) return 0;
    for (size_t k = 0; k < len; k++) {
        if (v1->val[k] != v2->val[k]) return 0;
    }
    return 1;
}

