#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "csr.h"

CSRGraph* create_csr_from_adj_list(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    CSRGraph *g = (CSRGraph*)malloc(sizeof(CSRGraph));
    if (!g) {
        fclose(f);
        return NULL;
    }

    // Determine if file is weighted based on file path name
    g->is_weighted = (strstr(filename, "weighted") && !strstr(filename, "unweighted")) ? 1 : 0;

    int V_count = 0, E_count = 0;

    // Read V and E from the header (Section 6.1 & 7.1)
    if (fscanf(f, "%d %d", &V_count, &E_count) != 2) {
        printf("Error: Invalid header in %s\n", filename);
        fclose(f);
        free(g);
        return NULL;
    }

    g->num_vertices = V_count;
    g->num_edges = E_count;
    g->row_ptr = (int*)calloc(V_count + 1, sizeof(int));

    int max_edges = (E_count > 0) ? (E_count * 2) : 100;
    g->col_idx = (int*)malloc(max_edges * sizeof(int));
    g->values  = (int*)malloc(max_edges * sizeof(int));

    int current_edge = 0;
    g->row_ptr[0] = 0;

    // Read adjacency list line-by-line
    for (int i = 0; i < V_count; i++) {
        int u = 0, degree = 0;
        if (fscanf(f, "%d %d", &u, &degree) != 2) break;

        for (int d = 0; d < degree; d++) {
            int v = 0, w = 1;

            if (g->is_weighted) {
                if (fscanf(f, "%d %d", &v, &w) != 2) break;
            } else {
                if (fscanf(f, "%d", &v) != 1) break;
            }

            if (current_edge >= max_edges) {
                max_edges *= 2;
                g->col_idx = (int*)realloc(g->col_idx, max_edges * sizeof(int));
                g->values  = (int*)realloc(g->values, max_edges * sizeof(int));
            }

            g->col_idx[current_edge] = v;
            g->values[current_edge]  = w;
            current_edge++;
        }
        g->row_ptr[u + 1] = current_edge;
    }

    // Fill forward for vertices with zero degree
    for (int i = 1; i <= V_count; i++) {
        if (g->row_ptr[i] < g->row_ptr[i - 1]) {
            g->row_ptr[i] = g->row_ptr[i - 1];
        }
    }

    g->num_edges = current_edge;

    // Trim dynamic memory to exact count
    if (current_edge > 0) {
        g->col_idx = (int*)realloc(g->col_idx, current_edge * sizeof(int));
        if (g->is_weighted) {
            g->values = (int*)realloc(g->values, current_edge * sizeof(int));
        } else {
            free(g->values);
            g->values = NULL;
        }
    } else {
        free(g->col_idx);
        free(g->values);
        g->col_idx = NULL;
        g->values = NULL;
    }

    fclose(f);
    return g;
}

void print_csr(const CSRGraph *g, const char *filename) {
    if (!g) return;

    printf("\nAlgorithm: CSR Representation\n");
    printf("File Name : %s\n", filename);

    // Print V (values) ONLY for weighted graphs (Section 2.2)
    if (g->is_weighted && g->values) {
        printf("V         = [ ");
        for (int i = 0; i < g->num_edges; i++) {
            printf("%d ", g->values[i]);
        }
        printf("]\n");
    }

    // Print COL_INDEX array
    printf("COL_INDEX = [ ");
    for (int i = 0; i < g->num_edges; i++) {
        printf("%d ", g->col_idx[i]);
    }
    printf("]\n");

    // Print ROW_INDEX array
    printf("ROW_INDEX = [ ");
    for (int i = 0; i <= g->num_vertices; i++) {
        printf("%d ", g->row_ptr[i]);
    }
    printf("]\n");
}

void free_csr(CSRGraph *g) {
    if (!g) return;
    if (g->row_ptr) free(g->row_ptr);
    if (g->col_idx) free(g->col_idx);
    if (g->values)  free(g->values);
    free(g);
}