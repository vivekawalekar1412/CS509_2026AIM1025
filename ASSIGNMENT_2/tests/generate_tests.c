#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_bf(const char *filename, int V, int deg) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    int E = V * deg;
    fprintf(fp, "%d %d\n", V, E);
    for (int i = 0; i < V; i++) {
        fprintf(fp, "%d %d", i, deg);
        for (int j = 1; j <= deg; j++) {
            int target = (i + j) % V;
            int weight = (rand() % 30) - 5; // Weights include negative values
            fprintf(fp, " %d %d", target, weight);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "SOURCE 0\n");
    fclose(fp);
}

void generate_fw(const char *filename, int V) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "%d\n", V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) fprintf(fp, "0 ");
            else if (rand() % 4 == 0) fprintf(fp, "INF ");
            else fprintf(fp, "%d ", (rand() % 20) + 1);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main() {
    srand(42); // Fixed seed for reproducibility
    
    // Bellman-Ford required sizes (sparse graphs: E approx 2V-4V)
    generate_bf("bellman_ford/bf_100.txt", 100, 3);
    generate_bf("bellman_ford/bf_10000.txt", 10000, 3);
    generate_bf("bellman_ford/bf_50000.txt", 50000, 3);
    generate_bf("bellman_ford/bf_100000.txt", 100000, 3);

    // Floyd-Warshall required sizes
    generate_fw("floyd_warshall/fw_100.txt", 100);
    generate_fw("floyd_warshall/fw_500.txt", 500);
    generate_fw("floyd_warshall/fw_1000.txt", 1000);
    generate_fw("floyd_warshall/fw_2000.txt", 2000);

    printf("All test files generated successfully.\n");
    return 0;
}