# SPMV-C: Sparse Matrix-Vector Multiplication in C

**SPMV-C** is a high-performance implementation of sparse matrix-vector multiplication (SpMV) using various optimization techniques in C. This project demonstrates multiple methods for matrix-vector multiplication, including:

- **Single-threaded implementation**
- **Multi-threaded implementation**
- **Compressed Row Storage (CRS/CSR) format**
- **Vectorized operations using AVX instructions**

The goal is to benchmark and compare the performance of these methods under different scenarios, such as varying matrix sizes and sparsity patterns.

## Features

- **Efficient Sparse Matrix Representation**: Utilizes the Compressed Row Format (CRF/CSR) to optimize memory usage and computational efficiency.
- **Multi-threading Support**: Implements multi-threaded SpMV using OpenMP to accelerate operations on multi-core processors.
- **AVX Vectorization**: Leverages AVX512 instructions to optimize matrix-vector operations on supported architectures.
- **Baseline Comparison**: Provides a basic matrix-vector multiplication implementation for performance comparison.

## Implemented Methods

1. **Baseline**: A straightforward implementation of matrix-vector multiplication.
2. **Single-threaded CSR**: Matrix-vector multiplication using the Compressed Row Storage format in a single thread.
3. **Multi-threaded CSR**: Parallelized matrix-vector multiplication using CSR with OpenMP for multi-threading.
4. **Vectorized**: A highly optimized version that uses AVX512 instructions to accelerate the operations.
5. **CRS Optimizations**: Compressed Row Storage-based implementation for sparse matrices, reducing memory overhead.

## Prerequisites

Before running the project, ensure you have the following installed:

- **GCC** with AVX512 support (if using the vectorized version)
- **OpenMP** for multi-threading

## How to Run

### Clone the repository:

```bash
git clone https://github.com/Arash1381-y/SPMV-C.git
cd SPMV-C
```

### Run benchmark
```bash
make
cd bin && benchmark
```

### Run tests
```bash
make test
cd bin && `TEST_NAME`
```


## Example Output

```terminal
REPORT OF SPARSE MATRIX MULTIPLICATION WITH 10000 ROWS AND 10000 COLUMNS AND SPARSITY OF 0.750000
________________________________________________________________________
|    Method     | Time taken (s) | Speedup  | Efficiency | Correctness |
|---------------|----------------|----------|------------|-------------|
|   Baseline    | 0.109          |     1    |    1       | true        |
|---------------|----------------|----------|------------|-------------|
| Single thread | 0.172          |  0.635   |  0.635     | true        |
|---------------|----------------|----------|------------|-------------|
|  Multi thread | 0.091          |  1.196   |  0.299     | true        |
|---------------|----------------|----------|------------|-------------|
|   Vectorized  | 0.031          |  3.560   |  3.560     | true        |
|---------------|----------------|----------|------------|-------------|
|       CSR     |  0.461         | 0.237    | 0.237      | true        |
|---------------|----------------|----------|------------|-------------|
```
