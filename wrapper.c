#include <stdio.h>
#include <stdlib.h>

void handle_assignment_1() {
    int task_choice, test_choice, gemm_mode;
    char command[512];

    printf("\n========================================\n");
    printf("             ASSIGNMENT 1               \n");
    printf("========================================\n");
    printf("1. CSR Conversion\n");
    printf("2. GEMM Matrix Multiplication\n");
    printf("0. Back to Main Menu\n");
    printf("Select Task: ");
    if (scanf("%d", &task_choice) != 1 || task_choice == 0) return;

    if (task_choice == 1) { // CSR
        printf("\n--- CSR Test Cases ---\n");
        printf("1. matrix_unweighted_10.txt\n");
        printf("2. matrix_unweighted_100.txt\n");
        printf("3. matrix_weighted_10.txt\n");
        printf("4. matrix_weighted_100.txt\n");
        printf("Select Test Case: ");
        if (scanf("%d", &test_choice) != 1) return;

        char *tests[] = {
            "ASSIGNMENT_1/tests/csr/matrix_unweighted_10.txt",
            "ASSIGNMENT_1/tests/csr/matrix_unweighted_100.txt",
            "ASSIGNMENT_1/tests/csr/matrix_weighted_10.txt",
            "ASSIGNMENT_1/tests/csr/matrix_weighted_100.txt"
        };
        if (test_choice >= 1 && test_choice <= 4) {
            snprintf(command, sizeof(command), ".\\ASSIGNMENT_1\\driver.exe csr %s", tests[test_choice - 1]);
            system(command);
        } else {
            printf("Invalid selection!\n");
        }
    } else if (task_choice == 2) { // GEMM
        printf("\n--- Select GEMM Variant ---\n");
        printf("1. Simple GEMM (gemm_simple)\n");
        printf("2. Blocked GEMM (gemm_blocking)\n");
        printf("Select Mode: ");
        if (scanf("%d", &gemm_mode) != 1) return;

        printf("\n--- GEMM Test Cases ---\n");
        printf("1. gemm_test_01.txt\n");
        printf("2. gemm_100.txt\n");
        printf("3. gemm_1000.txt\n");
        printf("Select Test Case: ");
        if (scanf("%d", &test_choice) != 1) return;

        char *tests[] = {
            "ASSIGNMENT_1/tests/gemm/gemm_test_01.txt",
            "ASSIGNMENT_1/tests/gemm/gemm_100.txt",
            "ASSIGNMENT_1/tests/gemm/gemm_1000.txt"
        };

        if (test_choice >= 1 && test_choice <= 3) {
            if (gemm_mode == 1) {
                snprintf(command, sizeof(command), ".\\ASSIGNMENT_1\\driver.exe gemm_simple %s", tests[test_choice - 1]);
                system(command);
            } else if (gemm_mode == 2) {
                snprintf(command, sizeof(command), ".\\ASSIGNMENT_1\\driver.exe gemm_blocking %s 16", tests[test_choice - 1]);
                system(command);
            } else {
                printf("Invalid GEMM variant!\n");
            }
        } else {
            printf("Invalid test file selection!\n");
        }
    }
}

void handle_assignment_2() {
    int task_choice, test_choice;
    char command[512];

    printf("\n========================================\n");
    printf("             ASSIGNMENT 2               \n");
    printf("========================================\n");
    printf("1. Bellman-Ford (Single-Source Shortest Path)\n");
    printf("2. Floyd-Warshall (All-Pairs Shortest Path)\n");
    printf("0. Back to Main Menu\n");
    printf("Select Algorithm: ");
    if (scanf("%d", &task_choice) != 1 || task_choice == 0) return;

    if (task_choice == 1) { // Bellman-Ford
        printf("\n--- Bellman-Ford Test Cases ---\n");
        printf("1. bf_10.txt\n");
        printf("2. bf_100.txt\n");
        printf("3. bf_10000.txt\n");
        printf("4. bf_50000.txt\n");
        printf("5. bf_100000.txt\n");
        printf("Select Test Case: ");
        if (scanf("%d", &test_choice) != 1) return;

        char *tests[] = {
            "ASSIGNMENT_2/tests/bellman_ford/bf_10.txt",
            "ASSIGNMENT_2/tests/bellman_ford/bf_100.txt",
            "ASSIGNMENT_2/tests/bellman_ford/bf_10000.txt",
            "ASSIGNMENT_2/tests/bellman_ford/bf_50000.txt",
            "ASSIGNMENT_2/tests/bellman_ford/bf_100000.txt"
        };
        if (test_choice >= 1 && test_choice <= 5) {
            snprintf(command, sizeof(command), ".\\ASSIGNMENT_2\\driver.exe bf %s", tests[test_choice - 1]);
            system(command);
        } else {
            printf("Invalid selection!\n");
        }
    } else if (task_choice == 2) { // Floyd-Warshall
        printf("\n--- Floyd-Warshall Test Cases ---\n");
        printf("1. fw_10.txt\n");
        printf("2. fw_100.txt\n");
        printf("3. fw_500.txt\n");
        printf("4. fw_1000.txt\n");
        printf("5. fw_2000.txt\n");
        printf("Select Test Case: ");
        if (scanf("%d", &test_choice) != 1) return;

        char *tests[] = {
            "ASSIGNMENT_2/tests/floyd_warshall/fw_10.txt",
            "ASSIGNMENT_2/tests/floyd_warshall/fw_100.txt",
            "ASSIGNMENT_2/tests/floyd_warshall/fw_500.txt",
            "ASSIGNMENT_2/tests/floyd_warshall/fw_1000.txt",
            "ASSIGNMENT_2/tests/floyd_warshall/fw_2000.txt"
        };
        if (test_choice >= 1 && test_choice <= 5) {
            snprintf(command, sizeof(command), ".\\ASSIGNMENT_2\\driver.exe fw %s", tests[test_choice - 1]);
            system(command);
        } else {
            printf("Invalid selection!\n");
        }
    }
}

void handle_assignment_3() {
    int task_choice, test_choice;
    char command[512];

    printf("\n========================================\n");
    printf("             ASSIGNMENT 3               \n");
    printf("========================================\n");
    printf("1. Kruskal's MST\n");
    printf("2. Prim's MST\n");
    printf("3. Compare Both (Kruskal & Prim)\n");
    printf("0. Back to Main Menu\n");
    printf("Select Option: ");
    if (scanf("%d", &task_choice) != 1 || task_choice == 0) return;

    const char *mode = "both";
    if (task_choice == 1) mode = "kruskal";
    else if (task_choice == 2) mode = "prim";
    else if (task_choice == 3) mode = "both";
    else {
        printf("Invalid selection!\n");
        return;
    }

    printf("\n--- MST Test Cases ---\n");
    printf("1. mst_10.txt\n");
    printf("2. mst_100.txt\n");
    printf("3. mst_10000.txt\n");
    printf("4. mst_50000.txt\n");
    printf("5. mst_100000.txt\n");
    printf("Select Test Case: ");
    if (scanf("%d", &test_choice) != 1) return;

    char *tests[] = {
        "ASSIGNMENT_3/tests/mst/mst_10.txt",
        "ASSIGNMENT_3/tests/mst/mst_100.txt",
        "ASSIGNMENT_3/tests/mst/mst_10000.txt",
        "ASSIGNMENT_3/tests/mst/mst_50000.txt",
        "ASSIGNMENT_3/tests/mst/mst_100000.txt"
    };

    if (test_choice >= 1 && test_choice <= 5) {
        snprintf(command, sizeof(command), ".\\ASSIGNMENT_3\\driver.exe %s %s", mode, tests[test_choice - 1]);
        system(command);
    } else {
        printf("Invalid test selection!\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n========================================\n");
        printf("      CS509 MASTER ASSIGNMENT MENU      \n");
        printf("========================================\n");
        printf("1. Access Assignment 1\n");
        printf("2. Access Assignment 2\n");
        printf("3. Access Assignment 3\n");
        printf("0. Exit Program\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1 || choice == 0) {
            printf("Exiting Master System...\n");
            break;
        }

        switch (choice) {
            case 1:
                handle_assignment_1();
                break;
            case 2:
                handle_assignment_2();
                break;
            case 3:
                handle_assignment_3();
                break;
            default:
                printf("Invalid choice! Please select 1, 2, 3, or 0.\n");
        }
    }
    return 0;
}