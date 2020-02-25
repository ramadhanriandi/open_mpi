#include <stdio.h>
#include <stdlib.h>
// #include <mpi.h>

int main(int argc, char** argv) {
    int n_node;
    int seed = 80;

    printf("Enter the number of nodes : ");
    scanf("%d", &n_node);

    int result[n_node];
    int matrix_distance[n_node][n_node];

    init_graph(n_node, matrix_distance, seed);

    print_matrix(n_node, matrix_distance);

    // this process must be made to be parallel
    for (int i = 0; i < n_node; i++) {
        fill_array(n_node, result, -1);
        dijkstra(n_node, matrix_distance, i, result);
        print_solution(n_node, result);
    }

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

void fill_array(int n_node, int array[], int value) {
    for (int i = 0; i < n_node; i++) {
        array[i] = value;
    }
}

int is_visited(int n_node, int visited[], int checked_value) {
    int i = 0;

    while (i < n_node) {
        if (visited[i] == checked_value) {
            return 1;
        }
        i++;
    }

    return 0;
}

int find_alternative(int n_node, int visited[], int result[], int current_idx) {
    int min_alternative = 999;
    int choosen_idx = -1;
    for (int i = 0; i < n_node; i++) {
        if (is_visited(n_node, visited, i) == 0 && result[i] != -1) {
            if (min_alternative > result[i]) {
                min_alternative = result[i];
                choosen_idx = i;
            }
        }
    }
    return choosen_idx != -1 ? choosen_idx : current_idx;
}

void dijkstra(int n_node, int (*matrix)[n_node], int source, int result[]) {
    int visited[n_node];
    int global_min = 999;
    int path_cost = 0;
    int next_idx_pos = 0;
    int current_idx_pos = source;
    int i = 0; 

    fill_array(n_node, visited, -1);

    while (i < n_node) {
        for (int j = 0; j < n_node; j++) {
            if (is_visited(n_node, visited, j) == 0) {
                if (j != current_idx_pos) {
                    if (matrix[current_idx_pos][j] != -1) {
                        if (result[j] == -1 || path_cost + matrix[current_idx_pos][j] < result[j]) {
                            result[j] = path_cost + matrix[current_idx_pos][j];
                            if (result[j] < global_min) {
                                global_min = result[j];
                                next_idx_pos = j;
                            }
                        }
                    } else {
                        if (result[j] != -1 && result[j] < global_min) {
                            global_min = result[j];
                            next_idx_pos = j;
                        }
                    }
                } else {
                    if (result[j] == -1) {
                        result[j] = 0;
                    }
                }
                
            }
        }

        visited[i] = current_idx_pos;

        if (current_idx_pos != next_idx_pos) {
            current_idx_pos = next_idx_pos;
            path_cost = global_min;
        } else {
            current_idx_pos = find_alternative(n_node, visited, result, current_idx_pos);
            next_idx_pos = current_idx_pos;
            path_cost = result[current_idx_pos];
        }
        global_min = 999;
        i++;
    }
}

void print_solution(int n_node, int result[]) {
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < n_node; i++) 
        printf("%d \t\t %d\n", i, result[i]);
}