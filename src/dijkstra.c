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
            if (i == j) {
                matrix[i][j] = 0;
            } else if (i < j) {
                int parity = rand() % seed;
                if (parity % 2 == 0) {
                    matrix[i][j] = -1;
                    matrix[j][i] = -1;
                } else {
                    matrix[i][j] = parity;
                    matrix[j][i] = parity;
                }
            }
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

void print_solution(int result[], int n_node) {
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < n_node; i++) 
        printf("%d \t\t %d\n", i, result[i]);
}