# ASSIGNMENT 1
# MPI Programming Tasks

This repository contains implementations of fundamental MPI (Message Passing Interface) programs, covering essential communication techniques used in parallel computing.

## 📌 Tasks Overview

### 1️⃣ Hello World Program
This program demonstrates the basic setup of an MPI environment. Each process prints a message indicating its rank and the total number of processes.

**Key Functions Used:**
- `MPI_Init` - Initializes the MPI environment.
- `MPI_Comm_rank` - Retrieves the rank of the process.
- `MPI_Comm_size` - Gets the total number of processes.
- `MPI_Finalize` - Terminates the MPI execution environment.

### 2️⃣ Sending and Receiving with MPI_Send and MPI_Recv
This program demonstrates point-to-point communication, where one process sends a message and another receives it.

**Key Functions Used:**
- `MPI_Send` - Sends a message from one process to another.
- `MPI_Recv` - Receives a message sent by another process.

### 3️⃣ Dynamic Receiving with MPI_Probe and MPI_Status
This program introduces dynamic message receiving, allowing a process to check for incoming messages before receiving them. This helps in handling messages of varying sizes.

**Key Functions Used:**
- `MPI_Probe` - Checks for incoming messages without receiving them.
- `MPI_Get_count` - Determines the size of the received message.
- `MPI_Status` - Holds information about the received message.

### 4️⃣ Point-to-Point Communication Application - Random Walking
This program simulates a random walk using MPI processes. Each process performs a step in the random walk and communicates with others to track movement.

**Key Concepts Used:**
- `MPI_Send` and `MPI_Recv` for message passing.
- Random number generation for walk direction.
- Synchronization among processes to ensure accurate simulation.

## 🔧 Compilation and Execution

### 🔹 Compilation
To compile any of the programs, use:
```sh
mpicc program_name.c -o program_name
```

### 🔹 Running the Programs
To execute with multiple processes:
```sh
mpirun -np <num_processes> ./program_name
```
Example:
```sh
mpirun -np 4 ./hello_world
```

## 📜 Requirements
- MPI Library (OpenMPI or MPICH)
- GCC Compiler
- Linux/macOS environment (or WSL for Windows users)

## 💡 Future Enhancements
- Extend point-to-point communication for more complex applications.
- Implement collective communication techniques such as `MPI_Bcast` and `MPI_Reduce`.
- Optimize random walk simulation with load balancing strategies.

## 🤝 Contributing
Feel free to submit pull requests for improvements or additional examples!

## 📄 License
This project is open-source and available under the MIT License.

