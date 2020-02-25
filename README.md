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
Kita menggunakan MPI Broadcast untuk mengirimkan data yang sama yaitu matriks yang berisi jarak terpendek dari setiap ke semua node lainnya. Matriks ini akan dikirimkan ke seluruh proses yang ada. Broadcast menggunakan jalur komunikasi berbentuk pohon.

### Analisis Solusi yang Diberikan
Berdasarkan solusi yang digunakan, kita menghasilkan kinerja yang lebih ringan dengan membagi proses untuk ditangani oleh beberapa thread.
Untuk menghasilkan solusi yang lebih baik, dapat dilakukan dengan cara mengoptimasi algoritma Dijkstra yang telah dibuat.
Selain itu kita dapat menggunakan fitur MPI yang lebih cocok seperti Scatter dan Gather untuk melakukan penyebaran dan pengumpulan data sehingga kinerja yang dihasilkan lebih baik.

### Jumlah Thread yang Digunakan
Kita menggunakan 4 thread karena disesuaikan dengan logical processor serta spesifikasi laptop atau server yang digunakan.

### Pengukuran Kinerja untuk Tiap Kasus Uji Dibandingkan dengan Dijkstra Algorithm Serial
https://gitlab.informatika.org/reyhankim/openmpi/-/raw/master/screenshots/serial_100.png

https://gitlab.informatika.org/reyhankim/openmpi/-/blob/master/screenshots/parallel_100.png

### Analisis Perbandingan Kinerja Serial dan Parallel
Pada umumnya, kinerja program parallel akan menghasilkan kinerja yang lebih baik daripada program serial. Namun pada percobaan tugas ini, hasil yang didapat dari program parallel tidak lebih baik daripada program serial yang telah dibuat.
Kedua program menggunakan algoritma dijkstra yang sama namun perbedaaannya terletak pada bagaimana terdapat beberapa proses di program parallel dalam mengelola data.
Hasil yang lebih buruk ini dapat disebabkan oleh kesalahan algoritma MPI atau kurang cocoknya fitur MPI yang digunakan dalam pembuatan proses parallel.

Hasil contoh pengujian terhadap waktu elapsed:

Parallel 100 : 222.552 ms

Serial 100 : 185.857 ms
