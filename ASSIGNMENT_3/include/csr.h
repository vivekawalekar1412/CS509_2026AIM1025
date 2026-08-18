#ifndef CSR_H
#define CSR_H

typedef struct {
    int V;
    int E;          // Total directed entries (or 2 * undirected E)
    int *row_ptr;
    int *col_idx;
    int *values;
} CSRGraph;

CSRGraph* read_and_convert_to_csr(const char *filename);
void free_csr(CSRGraph *graph);

#endif // CSR_H