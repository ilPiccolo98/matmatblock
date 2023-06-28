#!/bin/bash
#SBATCH --job-name=matmatthread
#SBATCH --output=matmatthread.out
#SBATCH --error=matmatthread.err
#SBATCH --time=00:60:00
#SBATCH --partition=sequential
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem-per-cpu=5000

# Set Stack size:
ulimit -s 10240

# Load module
#module load ompi-4.1.0-gcc-8.3.1
#module load cuda/11.2

# Run con mpi
#mpirun --bind-to none  ./a.out
cc   -o matmatthread main.c c_timer.c -O3  -Ofast -march=native -m64  -fopenmp -lm
./matmatthread

# Run
#./a.out

