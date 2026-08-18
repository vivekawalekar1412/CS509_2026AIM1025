#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../ASSIGNMENT_1/include/csr.h"
#include "../include/mst.h"

void print_output(const char *alg_name, const MSTResult *res) {
    printf("Algorithm: %s\n", alg_name);
    printf("MST edges:\n");
    for (int i = 0; i < res->count; ++i) {
        printf("%d %d %d\n", res->edges[i].u, res->edges[i].v, res->edges[i].weight);
    }
    printf("Total MST weight: %lld\n", (long long)res->total_weight);
    printf("Execution time: %.4f ms\n", res->execution_time_ms);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <kruskal|prim|both> <input_file_path>\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *filepath = argv[2];

    CSRGraph *csr = create_csr_from_adj_list(filepath);
    if (!csr) {
        fprintf(stderr, "Failed to load graph from %s\n", filepath);
        return 1;
    }

    if (strcmp(mode, "kruskal") == 0) {
        MSTResult k_res = run_kruskal(csr);
        print_output("Kruskal's MST", &k_res);
        free_mst_result(&k_res);
    } else if (strcmp(mode, "prim") == 0) {
        MSTResult p_res = run_prim(csr);
        print_output("Prim's MST", &p_res);
        free_mst_result(&p_res);
    } else if (strcmp(mode, "both") == 0) {
        MSTResult k_res = run_kruskal(csr);
        print_output("Kruskal's MST", &k_res);
        printf("\n");
        MSTResult p_res = run_prim(csr);
        print_output("Prim's MST", &p_res);
        free_mst_result(&k_res);
        free_mst_result(&p_res);
    } else {
        fprintf(stderr, "Unknown algorithm option: %s\n", mode);
        free_csr(csr);
        return 1;
    }

    free_csr(csr);
    return 0;
}