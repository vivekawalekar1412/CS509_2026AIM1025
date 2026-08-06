#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gemm.h"

void run_gemm_simple(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filepath);
        return;
    }

    int M, K, N;
    if (fscanf(file, "%d %d %d", &M, &K, &N) != 3) {
        fclose(file);
        return;
    }

    int *A = (int*) malloc(M * K * sizeof(int));
    int *B = (int*) malloc(K * N * sizeof(int));
    int *C = (int*) calloc(M * N, sizeof(int));

    for (int i = 0; i < M * K; i++) fscanf(file, "%d", &A[i]);
    for (int i = 0; i < K * N; i++) fscanf(file, "%d", &B[i]);
    fclose(file);

    clock_t start = clock();
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < K; k++) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    printf("\nAlgorithm: GEMM Simple\n");
    printf("Result matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i * N + j]);
        }
        printf("\n");
    }
    printf("Execution time: %.4f ms\n", time_taken);

    free(A); free(B); free(C);
}

void run_gemm_blocking(const char *filepath, int block_size) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filepath);
        return;
    }

    int M, K, N;
    if (fscanf(file, "%d %d %d", &M, &K, &N) != 3) {
        fclose(file);
        return;
    }

    int *A = (int*) malloc(M * K * sizeof(int));
    int *B = (int*) malloc(K * N * sizeof(int));
    int *C = (int*) calloc(M * N, sizeof(int));

    for (int i = 0; i < M * K; i++) fscanf(file, "%d", &A[i]);
    for (int i = 0; i < K * N; i++) fscanf(file, "%d", &B[i]);
    fclose(file);

    clock_t start = clock();
    for (int i0 = 0; i0 < M; i0 += block_size) {
        for (int j0 = 0; j0 < N; j0 += block_size) {
            for (int k0 = 0; k0 < K; k0 += block_size) {
                for (int i = i0; i < i0 + block_size && i < M; i++) {
                    for (int j = j0; j < j0 + block_size && j < N; j++) {
                        int sum = C[i * N + j];
                        for (int k = k0; k < k0 + block_size && k < K; k++) {
                            sum += A[i * K + k] * B[k * N + j];
                        }
                        C[i * N + j] = sum;
                    }
                }
            }
        }
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    printf("\nAlgorithm: GEMM Blocking\n");
    printf("Result matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i * N + j]);
        }
        printf("\n");
    }
    printf("Execution time: %.4f ms\n", time_taken);

    free(A); free(B); free(C);
}