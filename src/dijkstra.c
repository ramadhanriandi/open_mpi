#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int numtasks, rank, dest, source, rc, count, tag=1;
    clock_t t;

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

    // final distance matrix which will be outputted
    int final_matrix_distance[n_node][n_node];
    if (rank == 0) {
        for (int i = 0; i < n_node; i++) {
            fill_array(n_node, final_matrix_distance[i], -1);
        };

        init_graph(n_node, matrix_distance, seed);

        print_matrix(n_node, matrix_distance);
    }

    t = clock();
    int k = rank;
    // THIS PROCESS MUST BE MADE TO BE PARALLEL WITH OPENMPI
    while (k < n_node) {
        fill_array(n_node, result, -1);
        dijkstra(n_node, matrix_distance, k, result);
        for (int i = 0; i < n_node; i++) {
            final_matrix_distance[k][i] = result[i];
        }
        MPI_Bcast(&final_matrix_distance, 1, MPI_INT, rank, MPI_COMM_WORLD);

    //   k += numtasks;
        k++;
    }
    t = clock() - t;
    double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000);

    MPI_Finalize();

    // PRINT RESULT
    if (rank == 0) {
      printf("\n%s\n", "Final result:");
      print_matrix(n_node, final_matrix_distance);
      printf("\n%s%f%s\n", "Time elapsed: ", time_taken, " ms");
      print_matrix_to_file(n_node, final_matrix_distance);
    }

    return 0;
}

int read_n(int rank, MPI_Comm comm) {
  int n;

  if (rank == 0) {
    // printf("Enter the number of nodes : ");
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

void print_matrix_to_file(int n_node, int (*matrix)[n_node]) {
    FILE * fp;
    /* open the file for writing*/
    fp = fopen ("output.txt","w");

    for (int i = 0; i < n_node; i++) {
      for (int j = 0; j < n_node; j++) {
        fprintf(fp, "%d ", matrix[i][j]);
      }
      fprintf(fp, "\n");
    }

    /* close the file*/
    fclose (fp);
}