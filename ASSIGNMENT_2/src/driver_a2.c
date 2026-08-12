#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csr.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"

// Self-contained parser that reads Bellman-Ford weighted adjacency list directly into CSRGraph
CSRGraph* load_bf_csr_directly(const char *filepath, int *source_out) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("[ERROR] File not found: %s\n", filepath);
        return NULL;
    }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        printf("[ERROR] Invalid header in file: %s\n", filepath);
        fclose(fp);
        return NULL;
    }

    CSRGraph *graph = (CSRGraph *)malloc(sizeof(CSRGraph));
    graph->num_vertices = V;
    graph->num_edges = E;
    graph->is_weighted = 1;

    graph->row_ptr = (int *)malloc((V + 1) * sizeof(int));
    graph->col_idx = (int *)malloc(E * sizeof(int));
    graph->values = (int *)malloc(E * sizeof(int));

    graph->row_ptr[0] = 0;
    int edge_count = 0;

    for (int i = 0; i < V; i++) {
        int u, deg;
        if (fscanf(fp, "%d %d", &u, &deg) != 2) break;
        
        for (int j = 0; j < deg; j++) {
            int v, w;
            fscanf(fp, "%d %d", &v, &w);
            if (edge_count < E) {
                graph->col_idx[edge_count] = v;
                graph->values[edge_count] = w;
                edge_count++;
            }
        }
        graph->row_ptr[i + 1] = edge_count;
    }

    // Read SOURCE line if present
    char token[32];
    int source = 0;
    while (fscanf(fp, "%s", token) == 1) {
        if (strcmp(token, "SOURCE") == 0) {
            fscanf(fp, "%d", &source);
            break;
        }
    }
    fclose(fp);

    *source_out = source;
    return graph;
}

void parse_fw_file(const char* filepath, int *V_out, int ***matrix_out) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("[ERROR] Could not open file: %s\n", filepath);
        exit(EXIT_FAILURE);
    }
    int V;
    if (fscanf(fp, "%d", &V) != 1) {
        printf("[ERROR] Invalid Floyd-Warshall format in %s\n", filepath);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int **matrix = (int **)malloc(V * sizeof(int *));
    char token[32];
    for (int i = 0; i < V; i++) {
        matrix[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            fscanf(fp, "%s", token);
            if (strcmp(token, "INF") == 0) matrix[i][j] = INF;
            else matrix[i][j] = atoi(token);
        }
    }
    fclose(fp);
    *V_out = V;
    *matrix_out = matrix;
}

int main(int argc, char *argv[]) {
    printf("--- Running CS509 Assignment 2 Driver ---\n");
    fflush(stdout);

    if (argc < 3) {
        printf("Usage: %s <algorithm: bf|fw> <filepath>\n", argv[0]);
        return 1;
    }

    char *alg = argv[1];
    char *filepath = argv[2];

    if (strcmp(alg, "bf") == 0) {
        int source = 0;
        CSRGraph *graph = load_bf_csr_directly(filepath, &source);
        if (!graph) {
            printf("[ERROR] Failed to load graph for Bellman-Ford.\n");
            return 1;
        }

        run_bellman_ford(graph, source);
        free_csr(graph);
    } 
    else if (strcmp(alg, "fw") == 0) {
        int V;
        int **matrix;
        parse_fw_file(filepath, &V, &matrix);
        run_floyd_warshall(V, matrix);
    } 
    else {
        printf("[ERROR] Unknown algorithm choice '%s'\n", alg);
        return 1;
    }

    return 0;
}