#ifndef MST_H
#define MST_H

#include "../../ASSIGNMENT_1/include/csr.h"

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

typedef struct {
    Edge *edges;
    int count;
    long long total_weight;
    double execution_time_ms;
} MSTResult;

MSTResult run_kruskal(const CSRGraph *csr);
MSTResult run_prim(const CSRGraph *csr);
void free_mst_result(MSTResult *res);

#endif // MST_H