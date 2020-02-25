#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int numtasks, rank, dest, source, rc, count, tag=1;
    // if (argc != 3) {
    //     fprintf(stderr, "Usage: compare_bcast num_elements num_trials\n");
    //     exit(1);
    // }
    // int num_elements = atoi(argv[1]);
    // int num_trials = atoi(argv[2]);
    // MPI_Init(NULL, NULL);
    // int world_rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // double total_mpi_bcast_time = 0.0;
    // int i;
    // int matrix_distance[8][8];
    // init_graph(8, matrix_distance, 80);
    // // int* data = (int*)malloc(sizeof(int) * num_elements);
    // // assert(data != NULL);
    // for (i = 0; i < num_trials; i++) {
    //     // Time MPI_Bcast
    //     MPI_Barrier(MPI_COMM_WORLD);
    //     total_mpi_bcast_time -= MPI_Wtime();
    //     MPI_Bcast(matrix_distance, num_elements, MPI_INT, 0, MPI_COMM_WORLD);
    //     if (world_rank != 0) {
    //         print_matrix(8, matrix_distance);
    //     }
    //     MPI_Barrier(MPI_COMM_WORLD);
    //     total_mpi_bcast_time += MPI_Wtime();
    // }
    // // Print off timing information
    // if (world_rank == 0) {
    //     // printf("Data size = %d, Trials = %d\n", num_elements * (int)sizeof(int),
    //     // num_trials);
    //     printf("Avg MPI_Bcast time = %lf\n", total_mpi_bcast_time / num_trials);
    // }
    // MPI_Finalize();

    int n_node;
    int seed = 80;

    int name_len;

    MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    n_node = read_n(rank, MPI_COMM_WORLD);

    int result[n_node];
    int matrix_distance[n_node][n_node];

    init_graph(n_node, matrix_distance, seed);

    print_matrix(n_node, matrix_distance);

    int k = rank;
    // THIS PROCESS MUST BE MADE TO BE PARALLEL WITH OPENMPI
    while (k < n_node) {
      fill_array(n_node, result, -1);
      dijkstra(n_node, &matrix_distance, k, result);
      print_solution(n_node, result);
      MPI_Bcast(&matrix_distance, 1, MPI_INT, rank, MPI_COMM_WORLD);
      k += numtasks;
    }

    MPI_Finalize();

    // PRINT RESULT
    if (rank == 0) {
      printf("\n%s\n", "Final result:");
      print_solution(n_node, matrix_distance);
    }

    return 0;
}

int read_n(int rank, MPI_Comm comm) {
  int n;

  if (rank == 0) {
    printf("Enter the number of nodes : ");
    scanf("%d", &n);
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, comm);
  return n;
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
//        print_solution(n_node, visited);
        if (current_idx_pos != next_idx_pos) {
            current_idx_pos = next_idx_pos;
            path_cost = global_min;
//            printf("%d\n", next_idx_pos);
//            printf("tanpa alternatif\n");
        } else {
            current_idx_pos = find_alternative(n_node, visited, result, current_idx_pos);
            next_idx_pos = current_idx_pos;
            path_cost = result[current_idx_pos];
//            printf("%d\n", next_idx_pos);
//            printf("dengan alternatif\n");
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