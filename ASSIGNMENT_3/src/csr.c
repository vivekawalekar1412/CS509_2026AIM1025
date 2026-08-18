#include <stdio.h>
#include <stdlib.h>
#include "../include/csr.h"

CSRGraph* read_and_convert_to_csr(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open input file %s\n", filename);
        return NULL;
    }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        fprintf(stderr, "Error: Invalid graph header format in %s\n", filename);
        fclose(fp);
        return NULL;
    }

    CSRGraph *graph = (CSRGraph*)malloc(sizeof(CSRGraph));
    graph->V = V;
    graph->row_ptr = (int*)malloc((V + 1) * sizeof(int));

    // First pass or dynamic reading: Allocate maximum potential directed entries (2 * E)
    int max_entries = 2 * E;
    graph->col_idx = (int*)malloc(max_entries * sizeof(int));
    graph->values = (int*)malloc(max_entries * sizeof(int));

    graph->row_ptr[0] = 0;
    int current_idx = 0;

    for (int i = 0; i < V; ++i) {
        int u, deg;
        if (fscanf(fp, "%d %d", &u, &deg) != 2) {
            fprintf(stderr, "Error: Reading vertex degree for vertex %d\n", i);
            fclose(fp);
            free_csr(graph);
            return NULL;
        }
        for (int j = 0; j < deg; ++j) {
            int v, w;
            if (fscanf(fp, "%d %d", &v, &w) != 2) {
                fprintf(stderr, "Error: Reading neighbor info for vertex %d\n", u);
                fclose(fp);
                free_csr(graph);
                return NULL;
            }
            if (current_idx < max_entries) {
                graph->col_idx[current_idx] = v;
                graph->values[current_idx] = w;
                current_idx++;
            }
        }
        graph->row_ptr[i + 1] = current_idx;
    }

    graph->E = current_idx;
    fclose(fp);
    return graph;
}

void free_csr(CSRGraph *graph) {
    if (graph) {
        if (graph->row_ptr) free(graph->row_ptr);
        if (graph->col_idx) free(graph->col_idx);
        if (graph->values) free(graph->values);
        free(graph);
    }
}