# ASSIGNMENT 2

This repository contains implementations of fundamental MPI-based parallel computing algorithms, demonstrating various message-passing and computation techniques. Each task has been implemented using MPI for distributed computing and OpenMP for performance measurement.

## 📌 Tasks Overview

### 1️⃣ Estimate the Value of Pi Using the Monte Carlo Method
This program estimates the value of π using the Monte Carlo method, leveraging MPI for parallel execution. Each process generates random points and checks if they fall inside a unit circle. The results are aggregated using MPI.

**Key Functions Used:**
- `MPI_Init`, `MPI_Finalize`
- `MPI_Comm_rank`, `MPI_Comm_size`
- `MPI_Reduce` for summing results across processes.
 -
  -<img width="197" alt="image" src="https://github.com/user-attachments/assets/0f90f6b1-0fa9-4194-ac3c-18c67cd81860" />


### 2️⃣ Matrix Multiplication Using MPI
This program performs matrix multiplication on a **70x70** matrix using MPI and compares the execution time with a serial implementation. Each process computes specific rows of the resulting matrix in parallel.

**Key Features:**
- Uses `MPI_Bcast` to distribute matrices.
- Measures execution time with `omp_get_wtime()`.
- Uses `MPI_Gather` to collect computed rows.

- <img width="271" alt="image" src="https://github.com/user-attachments/assets/402b98d5-e989-4a9d-b605-2ca90b100e79" />


### 3️⃣ Parallel Sorting Using MPI (Odd-Even Sort)
Implements Odd-Even Transposition Sort in parallel using MPI to sort an array across multiple processes.

**Key Concepts:**
- `MPI_Send` and `MPI_Recv` for exchanging elements.
- Alternates between even and odd phases for sorting.
- Uses `MPI_Comm_rank` and `MPI_Comm_size` for distributed execution.

-<img width="293" alt="image" src="https://github.com/user-attachments/assets/9bba8a72-d03a-477f-afd1-331804cebcb4" />


### 4️⃣ Heat Distribution Simulation Using MPI
Simulates heat distribution over a 2D grid using iterative updates and MPI for parallel computation. The grid updates over multiple iterations, simulating thermal conduction.

**Key Features:**
- Uses `MPI_Sendrecv` for ghost cell exchange between neighboring processes.
- Applies iterative Jacobi relaxation method.
- Measures execution time with `omp_get_wtime()`.
-
-    <img width="250" alt="image" src="https://github.com/user-attachments/assets/526e56bc-00d9-4ccf-a18c-1b45a7e1e01c" />


### 5️⃣ Parallel Reduction Using MPI
Implements a parallel reduction operation to compute a sum, maximum, or minimum value across multiple processes using MPI.

**Key Functions Used:**
- `MPI_Reduce` for computing results in a tree-based manner.
- `MPI_Allreduce` for broadcasting results to all processes.
- `MPI_Scatter` and `MPI_Gather` for efficient data distribution.
  -
  -<img width="176" alt="image" src="https://github.com/user-attachments/assets/0e07c61b-04d7-4a54-a42d-b903a1709e74" />


### 6️⃣ Parallel Dot Product Using MPI
Computes the dot product of two large vectors using MPI parallelism. Each process calculates partial dot products and sends them to the root process for final summation.

**Key Concepts:**
- Distributes vector segments among processes.
- Uses `MPI_Reduce` to sum partial results efficiently.
- Measures execution time using `omp_get_wtime()`.
 -
 -  <img width="261" alt="image" src="https://github.com/user-attachments/assets/2b031e36-9575-4fc3-9987-31a64ebfd88f" />


### 7️⃣ Parallel Prefix Sum (Scan) Using MPI
Computes the prefix sum (scan) of an array using parallel techniques in MPI. Each process computes partial sums which are then combined.

**Key Features:**
- Uses `MPI_Scan` for cumulative sum calculation.
- Efficient communication for parallel computation.
  -
  -<img width="178" alt="image" src="https://github.com/user-attachments/assets/878f0379-ce50-4b2e-bae3-d3937664812a" />


### 8️⃣ Parallel Matrix Transposition Using MPI
Transposes a large matrix in parallel using MPI communication primitives. Data is exchanged efficiently across processes to achieve transposition.

**Key Techniques:**
- `MPI_Sendrecv` for exchanging rows and columns.
- Row-wise distribution of data among processes.
- Performance comparison with serial execution.

- <img width="218" alt="image" src="https://github.com/user-attachments/assets/63024380-9ea5-4d2b-ba8f-f25175a6232a" />


## 🔧 Compilation and Execution

### 🔹 Compilation
Use the following command to compile any MPI program:
```sh
mpicc program_name.c -o program_name -fopenmp
```

### 🔹 Running the Programs
To execute with multiple processes:
```sh
mpirun -np <num_processes> ./program_name
```
Example:
```sh
mpirun -np 4 ./monte_carlo_pi
```

## 📜 Requirements
- MPI Library (OpenMPI or MPICH)
- GCC Compiler
- Linux/macOS environment (or WSL for Windows users)

## 💡 Future Enhancements
- Optimize communication overhead for better scalability.
- Implement hybrid MPI + OpenMP versions for improved efficiency.

## 🤝 Contributing
Feel free to submit pull requests with improvements or new implementations!

## 📄 License
This project is open-source and available under the MIT License.

