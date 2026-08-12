#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "floyd_warshall.h"

void run_floyd_warshall(int V, int **matrix) {
    // Allocate distance matrix
    int **dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) dist[i][j] = matrix[i][j];
    }

    // Start algorithm timing
    clock_t start = clock();

    // Dynamic Programming core logic
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Check diagonal for negative cycles
    bool has_neg_cycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            has_neg_cycle = true;
            break;
        }
    }

    // End algorithm timing
    clock_t end = clock();
    double execution_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Output formatting
    printf("Algorithm: Floyd-Warshall\n");
    if (has_neg_cycle) {
        printf("Negative cycle: true\n");
    } else {
        printf("Distance matrix:\n");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) printf("INF ");
                else printf("%d ", dist[i][j]);
            }
            printf("\n");
        }
        printf("Negative cycle: none\n");
    }
    printf("Execution time: %.2f ms\n", execution_time);

    for (int i = 0; i < V; i++) free(dist[i]);
    free(dist);
}