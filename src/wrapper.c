#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gemm.h"
#include "csr.h"

void select_gemm_test_file(char *filepath) {
    int file_choice;
    printf("\n--- Select GEMM Test File ---\n");
    printf("1. gemm_100.txt\n");
    printf("2. gemm_1000.txt\n");
    printf("3. gemm_test_01.txt\n");
    printf("4. Custom File Path\n");
    printf("Select Choice: ");
    
    if (scanf("%d", &file_choice) != 1) file_choice = 3;

    switch (file_choice) {
        case 1: strcpy(filepath, "tests/gemm/gemm_100.txt"); break;
        case 2: strcpy(filepath, "tests/gemm/gemm_1000.txt"); break;
        case 3: strcpy(filepath, "tests/gemm/gemm_test_01.txt"); break;
        case 4:
            printf("Enter Custom File Path: ");
            scanf("%s", filepath);
            break;
        default: strcpy(filepath, "tests/gemm/gemm_test_01.txt");
    }
}

void select_csr_test_file(char *filepath) {
    int file_choice;
    printf("\n--- Select CSR Graph Test File ---\n");
    printf("1. matrix_unweighted_10.txt\n");
    printf("2. matrix_unweighted_100.txt\n");
    printf("3. matrix_weighted_10.txt\n");
    printf("4. matrix_weighted_100.txt\n");
    printf("5. Custom File Path\n");
    printf("Select Choice: ");
    
    if (scanf("%d", &file_choice) != 1) file_choice = 1;

    switch (file_choice) {
        case 1: strcpy(filepath, "tests/csr/matrix_unweighted_10.txt"); break;
        case 2: strcpy(filepath, "tests/csr/matrix_unweighted_100.txt"); break;
        case 3: strcpy(filepath, "tests/csr/matrix_weighted_10.txt"); break;
        case 4: strcpy(filepath, "tests/csr/matrix_weighted_100.txt"); break;
        case 5:
            printf("Enter Custom File Path: ");
            scanf("%s", filepath);
            break;
        default: strcpy(filepath, "tests/csr/matrix_unweighted_10.txt");
    }
}

int main() {
    int choice;
    char filepath[256];

    while (1) {
        printf("\n================ CS509 ASSIGNMENT 1 ================\n");
        printf("1. GEMM (Simple & Blocking)\n");
        printf("2. CSR Graph Representation\n");
        printf("3. Exit\n");
        printf("Select Choice: ");
        
        if (scanf("%d", &choice) != 1 || choice == 3) {
            printf("Exiting program...\n");
            break;
        }

        switch (choice) {
            case 1:
                select_gemm_test_file(filepath);
                run_gemm_simple(filepath);
                run_gemm_blocking(filepath, 16);
                break;
            case 2: {
                select_csr_test_file(filepath);
                CSRGraph *graph = create_csr_from_adj_list(filepath);
                if (graph) {
                    print_csr(graph, filepath);
                    free_csr(graph);
                }
                break;
            }
            default:
                printf("Invalid Choice. Please enter 1, 2, or 3.\n");
        }
    }
    return 0;
}