# OpenMPI Dijkstra

## Petunjuk Penggunaan Program
1.  Jika program belum di-compile, lakukan perintah berikut pada terminal atau command prompt di direktori file dijkstra.c.
    
    `mpicc dijkstra.c -o dijkstra`

2.  Setelah berhasil di-compile, jalankan program dengan perintah berikut.

    `mpirun -np <jumlah-proses> --hostfile mpi_hostfile dijkstra`
    
    Tambahkan `--bind-to core:overload-allowed` jika terdapat permasalahan untuk jumlah proses yang besar.