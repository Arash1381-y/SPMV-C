gcc -o bench.out test_bench.c matrix_mult_CSR_single_thread.c ./../../data-structure/matrix.c ./../../data-structure/vec.c ./../../utils/spmv_rand_gen.c ./../baseline/matrix_mult_baseline.c

./bench.out

rm bench.out
