# MPI ASSIGNMENT 3

This repository contains implementations of key MPI-based parallel computing tasks, showcasing distributed computing techniques.

## 📌 Tasks Overview

### 1️⃣ DAXPY Loop
Implements the **DAXPY (Double precision A*X Plus Y) operation** using MPI for parallel computation and compares the speedup over a serial implementation.

**Key Concepts:**
- Each process computes a portion of the vector operation.
- Uses `MPI_Scatter` to distribute vector segments.
- Uses `MPI_Gather` to collect results.
- Measures execution time using `MPI_Wtime()`.

**Expected Output:**
```
MPI DAXPY Execution Time: 0.002345 seconds
Serial DAXPY Execution Time: 0.010567 seconds
Speedup: 4.5x
```

### 2️⃣ Calculation of π Using MPI_Bcast and MPI_Reduce
Parallel computation of π using numerical integration, leveraging **MPI_Bcast** and **MPI_Reduce**.

**Key Functions Used:**
- `MPI_Bcast` to share `num_steps` among all processes.
- Each process computes a portion of the sum.
- `MPI_Reduce` aggregates results to compute π.
- Measures execution time using `MPI_Wtime()`.

**Expected Output:**
```
Calculated value of π: 3.1415926535
Execution Time: 0.003678 seconds
```

### 3️⃣ Parallel Prime Number Finder Using MPI
Finds all prime numbers up to a given maximum using **MPI_Send** and **MPI_Recv** for task distribution.

**Algorithm Overview:**
1. Master process waits for requests from slaves using `MPI_Recv`.
2. If the message is **zero**, the process is starting; **negative**, the number is not prime; **positive**, the number is prime.
3. Master sends numbers to test using `MPI_Send`.
4. Slave processes test the number and return results.

**Expected Output:**
```
Prime numbers up to 50: 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47
Execution Time: 0.004321 seconds
```

### 🔧 Compilation and Execution

#### 🔹 Compilation
To compile any MPI program, use:
```sh
mpicc program_name.c -o program_name -fopenmp
```

#### 🔹 Running the Programs
To execute with multiple processes:
```sh
mpirun -np <num_processes> ./program_name
```
Example:
```sh
mpirun -np 4 ./mpi_daxpy
```

## 📜 Requirements
- MPI Library (OpenMPI or MPICH)
- GCC Compiler
- Linux/macOS environment (or WSL for Windows users)

## 💡 Future Enhancements
- Optimize communication patterns for improved scalability.
- Hybrid MPI + OpenMP implementations.

## 🤝 Contributing
Pull requests with optimizations and new MPI implementations are welcome!

## 📄 License
This project is open-source and available under the MIT License.

