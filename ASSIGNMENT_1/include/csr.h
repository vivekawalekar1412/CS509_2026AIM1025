#ifndef CSR_H
#define CSR_H

typedef struct {
    int num_vertices;
    int num_edges;
    int is_weighted;
    int *row_ptr;
    int *col_idx;
    int *values;
} CSRGraph;

CSRGraph* create_csr_from_adj_list(const char *filepath);
void free_csr(CSRGraph *graph);
void print_csr(const CSRGraph *graph, const char *filename);

#endif