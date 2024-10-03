gcc -o bench.out test_bench.c matrix_mult_CSR_vectorize.c  ./../../data-structure/matrix.c ./../../data-structure/vec.c ./../../utils/spmv_rand_gen.c ./../baseline/matrix_mult_baseline.c -mavx511f

./bench.out

rm bench.out