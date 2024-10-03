gcc -o bench.out test_bench.c ./../data-structure/matrix.c ./../data-structure/vec.c ./baseline/matrix_mult_baseline.c ./sparse-multithread/matrix_mult_CSR_multi_thread.c ./sparse-singlethread/matrix_mult_CSR_single_thread.c ./vectorize/matrix_mult_CSR_vectorize.c ./../utils/spmv_rand_gen.c -mavx512f

./bench.out

rm bench.out