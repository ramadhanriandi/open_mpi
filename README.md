# OpenMPI Dijkstra

## Petunjuk Penggunaan Program
1.  Jika program belum di-compile, lakukan perintah berikut pada terminal atau command prompt di direktori file dijkstra.c.
    
    `mpicc dijkstra.c -o dijkstra`

2.  Setelah berhasil di-compile, jalankan program dengan perintah berikut.

    `mpirun -np <jumlah-proses> --hostfile mpi_hostfile dijkstra`
    
    Tambahkan `--bind-to core:overload-allowed` jika terdapat permasalahan untuk jumlah proses yang besar.
    
## Pembagian Tugas
Berikut adalah pembagian tugas yang diterapkan.

| NIM | Nama | Pembagian Tugas | Kontribusi |
| ------ | ------ | ------ | ------ | 
| 13517029 | Reyhan Naufal Hakim | OpenMPI integration, main, read_n, print_matrix_to_file | 50% |
| 13517080 | Mgs. Muhammad Riandi Ramadhan | init_graph, dijkstra, print_matrix, fill_array, is_visited, find_alternative, print_solution | 50% | 

