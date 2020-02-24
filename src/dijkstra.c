#include <stdio.h>
#include <stdlib.h>
// #include <mpi.h>

int main(int argc, char** argv) {
    int n_node;
    int seed = 80;

    printf("Enter the number of nodes : ");
    scanf("%d", &n_node);

    int matrix_distance[n_node][n_node];

    init_graph(n_node, matrix_distance, seed);
    print_matrix(n_node, matrix_distance);

    return 0;
}

void init_graph(int n_node, int (*matrix)[n_node], int seed) {
    for (int i = 0; i < n_node; i++) {
        for (int j = 0; j < n_node; j++) {
            matrix[i][j] = rand() % seed;
        }
    }
}

void print_matrix(int n_node, int (*matrix)[n_node]) {
    for (int i = 0; i < n_node; i++) {
        for (int j = 0; j < n_node; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}