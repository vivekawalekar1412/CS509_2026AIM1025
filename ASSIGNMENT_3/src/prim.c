#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "../include/mst.h"

MSTResult run_prim(const CSRGraph *csr) {
    MSTResult result;
    result.count = 0;
    result.total_weight = 0;
    result.edges = (Edge *)malloc((csr->num_vertices > 0 ? (size_t)(csr->num_vertices - 1) : 1) * sizeof(Edge));

    clock_t start_clk = clock();

    int n = csr->num_vertices;
    int *visited = (int *)calloc((size_t)n, sizeof(int));
    int *key = (int *)malloc((size_t)n * sizeof(int));
    int *parent = (int *)malloc((size_t)n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n; ++count) {
        int min_val = INT_MAX, u = -1;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && key[v] < min_val) {
                min_val = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        if (parent[u] != -1) {
            result.edges[result.count].u = parent[u];
            result.edges[result.count].v = u;
            result.edges[result.count].weight = min_val;
            result.total_weight += min_val;
            result.count++;
        }

        for (int idx = csr->row_ptr[u]; idx < csr->row_ptr[u + 1]; ++idx) {
            int v = csr->col_idx[idx];
            int w = csr->values ? csr->values[idx] : 1;
            if (!visited[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }

    clock_t end_clk = clock();
    result.execution_time_ms = ((double)(end_clk - start_clk) / CLOCKS_PER_SEC) * 1000.0;

    free(visited);
    free(key);
    free(parent);
    return result;
}