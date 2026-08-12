#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "bellman_ford.h"

#define INF 1000000000

void run_bellman_ford(CSRGraph *graph, int source) {
    int V = graph->num_vertices;
    int *dist = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[source] = 0;

    // Start timing strictly before algorithm execution
    clock_t start = clock();

    // Relaxation passes (V - 1 times)
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            for (int idx = graph->row_ptr[u]; idx < graph->row_ptr[u + 1]; idx++) {
                int v = graph->col_idx[idx];
                int weight = graph->values[idx];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Extra pass for negative-weight cycle check
    bool has_neg_cycle = false;
    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        for (int idx = graph->row_ptr[u]; idx < graph->row_ptr[u + 1]; idx++) {
            int v = graph->col_idx[idx];
            int weight = graph->values[idx];
            if (dist[u] + weight < dist[v]) {
                has_neg_cycle = true;
                break;
            }
        }
        if (has_neg_cycle) break;
    }

    // Stop timing
    clock_t end = clock();
    double execution_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Output formatting strictly matching assignment rules
    printf("Algorithm: Bellman-Ford\n");
    printf("Source: %d\n", source);

    if (has_neg_cycle) {
        printf("Negative cycle: true\n");
    } else {
        printf("Vertex\tDistance\n");
        // Loop through all V vertices without truncating
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF) printf("%d\tINF\n", i);
            else printf("%d\t%d\n", i, dist[i]);
        }
        printf("Negative cycle: none\n");
    }
    printf("Execution time: %.2f ms\n", execution_time);
    fflush(stdout);

    free(dist);
}