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

## Laporan Pengerjaan
Berikut adalah laporan pengerjaan dari tugas ini.

### Deskripsi Solusi Parallel
Pada pengerjaan tugas ini, dilakukan proses pencarian jarak terpendek dari setiap node ke semua node lainnya.
Untuk mencari jarak terpendek dengan suatu source node tertentu, kita menggunakan algoritma dijkstra untuk melakukan penelusuran yang menghasilkan array yang berisi jarak terpendak source node tersebut ke semua node lainnya.
Untuk mendapatkan matriks yang berisi jarak terpendek dari setiap node ke semua node lainnya, algoritma dijkstra yang diterapkan pada setiap node dijalankan secara parallel dan setiap hasil array jarak terpendek dari algoritma tersebut akan disatukan menjadi sebuah matriks.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~ [SOLUSI] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Analisis Solusi yang Diberikan

### Jumlah Thread yang Digunakan

### Pengukuran Kinerja untuk Tiap Kasus Uji Dibandingkan dengan Dijkstra Algorithm Serial

### Analisis Perbandingan Kinerja Serial dan Paralel
