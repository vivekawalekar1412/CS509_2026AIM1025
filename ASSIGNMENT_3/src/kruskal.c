#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "../include/mst.h"

typedef struct {
    int parent;
    int rank;
} DSU;

static int find_set(DSU *dsu, int v) {
    if (v == dsu[v].parent)
        return v;
    return dsu[v].parent = find_set(dsu, dsu[v].parent);
}

static void union_sets(DSU *dsu, int a, int b) {
    a = find_set(dsu, a);
    b = find_set(dsu, b);
    if (a != b) {
        if (dsu[a].rank < dsu[b].rank) {
            int temp = a; a = b; b = temp;
        }
        dsu[b].parent = a;
        if (dsu[a].rank == dsu[b].rank)
            dsu[a].rank++;
    }
}

static int compare_edges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->weight < e2->weight) return -1;
    if (e1->weight > e2->weight) return 1;
    return 0;
}

MSTResult run_kruskal(const CSRGraph *csr) {
    MSTResult result;
    result.count = 0;
    result.total_weight = 0;
    result.edges = (Edge*)malloc((csr->V > 0 ? csr->V - 1 : 0) * sizeof(Edge));

    // Start timing inside the algorithm routine (per Section 8 rules)
    auto start_time = std::chrono::high_resolution_clock::now();

    // Extract unique undirected edges from CSR
    Edge *all_edges = (Edge*)malloc((csr->E) * sizeof(Edge));
    int edge_count = 0;

    for (int u = 0; u < csr->V; ++u) {
        for (int idx = csr->row_ptr[u]; idx < csr->row_ptr[u + 1]; ++idx) {
            int v = csr->col_idx[idx];
            int w = csr->values[idx];
            if (u < v) { // Only take each undirected edge once
                all_edges[edge_count].u = u;
                all_edges[edge_count].v = v;
                all_edges[edge_count].weight = w;
                edge_count++;
            }
        }
    }

    qsort(all_edges, edge_count, sizeof(Edge), compare_edges);

    DSU *dsu = (DSU*)malloc(csr->V * sizeof(DSU));
    for (int i = 0; i < csr->V; ++i) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    int selected = 0;
    for (int i = 0; i < edge_count && selected < csr->V - 1; ++i) {
        int u = all_edges[i].u;
        int v = all_edges[i].v;
        if (find_set(dsu, u) != find_set(dsu, v)) {
            union_sets(dsu, u, v);
            result.edges[selected] = all_edges[i];
            result.total_weight += all_edges[i].weight;
            selected++;
        }
    }
    result.count = selected;

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    result.execution_time_ms = duration.count();

    free(dsu);
    free(all_edges);
    return result;
}

void free_mst_result(MSTResult *res) {
    if (res && res->edges) {
        free(res->edges);
        res->edges = NULL;
    }
}