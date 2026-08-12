#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gemm.h"
#include "csr.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <algorithm> <input_file_path> [block_size]\n", argv[0]);
        printf("Supported Algorithms: csr, gemm_simple, gemm_blocking\n");
        return 1;
    }

    char *algo = argv[1];
    char *filepath = argv[2];

    if (strcmp(algo, "csr") == 0) {
        CSRGraph *graph = create_csr_from_adj_list(filepath);
        if (!graph) {
            printf("Error loading CSR graph.\n");
            return 1;
        }
        print_csr(graph, filepath);
        free_csr(graph);
    } else if (strcmp(algo, "gemm_simple") == 0) {
        run_gemm_simple(filepath);
    } else if (strcmp(algo, "gemm_blocking") == 0) {
        int block_size = (argc >= 4) ? atoi(argv[3]) : 16;
        run_gemm_blocking(filepath, block_size);
    } else {
        printf("Error: Unknown algorithm '%s'\n", algo);
        return 1;
    }

    return 0;
}