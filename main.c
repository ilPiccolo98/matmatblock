#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "c_timer.h"
#define MIN_RANDOM_NUMBER -1000
#define MAX_RANDOM_NUMBER 1000
#define BLOCK_SIZE 256

double get_random_number(double min, double max)
{
    double scale = rand() / (double) RAND_MAX;
	return min + scale * (max - (min));
    return rand() % 20;
}

void print_matrix(double *matrix, int rows, int columns)
{
    int row, column;
    for(row = 0; row != rows; ++row)
    {
        printf("Row: %d\n", row + 1);
        for(column = 0; column != columns; ++column)
            printf("%f ", matrix[row * columns + column]);
        puts("");
    }
}

double* init_matrix(int rows, int columns)
{
    double *matrix = (double*)calloc(rows * columns, sizeof(double));
    int row, column;
    for(row = 0; row != rows; ++row)
        for(column = 0; column != columns; ++column)
            matrix[row * columns + column] = get_random_number(MIN_RANDOM_NUMBER, MAX_RANDOM_NUMBER);
    return matrix;
}

void matmatikj(int ldA, int ldB, int ldC, double *A, double *B, double *C, int N, int M, int P)
{
    int i, k, j;
    for (i = 0; i < N; ++i)
        for (k = 0; k < P; ++k)
            for (j = 0; j < M; ++j)
                C[i * ldC + j] = C[i * ldC + j] + A[i * ldA + k] * B[k * ldB + j];
}

void matmatblock(int ldA, int ldB, int ldC, double *A, double *B, double *C, int N, int M, int P, int dbA, int dbB, int dbC)
{
    int i, k, j;
    for (i = 0; i < N / dbA; ++i)
        for (j = 0; j < M / dbB; ++j)
            for (k = 0; k < P / dbC; ++k)
                matmatikj(ldA, ldB, ldC, &A[i * ldA * dbA + j * dbA], &B[j * ldB * dbB + k * dbB], &C[i * ldC * dbA + k * dbC], dbA, dbB, dbC);
}

void print_performance(long double start, long double end, int dimension)
{
    long double time = end - start;
    long double complexity = 2 * pow(dimension, 3) / time / pow(10, 9);
    printf("Block dimension: %d; Dimension: %d; Time: %Lf; Gflops: %Lf\n", BLOCK_SIZE, dimension, time, complexity);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int i;
    for(i = BLOCK_SIZE; i <= 2048; i += BLOCK_SIZE)
    {
        double *A = init_matrix(i, i);
        double *B = init_matrix(i, i);
        double *C = init_matrix(i, i);
        long double start = get_cur_time();
        matmatblock(i, i, i, A, B, C, i, i, i, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        long double end = get_cur_time();
        print_performance(start, end, i);
        free(A);
        free(B);
        free(C);
    }
    return 0;
}