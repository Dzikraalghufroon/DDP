#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

struct PosAnggaran {
  char pos[50];
  long batas_nominal;
};
struct Transaksi {
    char kode[10];
    char jenis[20];
    char pos[50];
    long nominal;
    char tanggal[20];
    char keterangan[50];
};

struct RekapPengeluaran{
  char pos[50];
  long nominal;
  long realisasi;
  long sisa;
  int jumlah_transaksi;
  char status[10];
};

void clearScreen();
void header();
void tampilan_menu_riwayat_transaksi();
void realisasi_transaksi_table(struct Transaksi *data, int jumlah);
void tambah_ukuran_array_transaksi(struct Transaksi **arr, int *kapasitas);

/* =======================================================
        MODUL : get_transaksi
        DESKRIPSI : sebuah fungsi yang akan mengembalikan nilai dari data transaksi
        INPUT : variabel dengan nama jumlah_out berupa pointer 
        OUTPUT : data transaksi didapatkan dan ditampung dalam array struct Transaksi dan variabel jumlah_out memiliki nilai ukuran dari si array yang direturn
   =======================================================*/

struct Transaksi *get_transaksi(int *jumlah_out){
    int kapasitas = 10;
    *jumlah_out = 0;
    char line[150];
    struct Transaksi dataTransaksi;
    struct Transaksi *data = malloc(kapasitas * sizeof(struct Transaksi));
    if (!data) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(data);
        return NULL;
    }
    while (fgets(line, sizeof(line), readFile)) {

        if (sscanf(line, "%9[^|]|%19[^|]|%49[^|]|%19[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) != 6) {
            continue;
        }


        // Perlu perbesar kapasitas
        if (*jumlah_out == kapasitas) {
            tambah_ukuran_array_transaksi(&data, &kapasitas);
        }
        
        // Simpan
        data[*jumlah_out] = dataTransaksi;
        (*jumlah_out)++;
        
    }
    fclose(readFile);
    return data;
}

/* =======================================================
        MODUL : get_transaksi_pemasukan
        DESKRIPSI : sebuah fungsi yang akan mengembalikan nilai dari data transaksi pemasukan
        INPUT : variabel dengan nama jumlah_out berupa pointer 
        OUTPUT : data transaksi dari pemasukan didapatkan dan ditampung dalam array struct Transaksi dan variabel jumlah_out memiliki nilai ukuran dari si array yang direturn
   =======================================================*/

struct Transaksi *get_transaksi_pemasukan(int *jumlah_out){
    int kapasitas = 10;
    *jumlah_out = 0;
    char line[150];
    struct Transaksi dataTransaksi;
    struct Transaksi *data = malloc(kapasitas * sizeof(struct Transaksi));
    if (!data) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(data);
        return NULL;
    }
    while (fgets(line, sizeof(line), readFile)) {

        if (sscanf(line, "%9[^|]|%19[^|]|%49[^|]|%19[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) != 6) {
            continue;
        }

        if (strcmp(dataTransaksi.jenis, "Pemasukan") == 0) {

            // Perlu perbesar kapasitas
            if (*jumlah_out == kapasitas) {
                tambah_ukuran_array_transaksi(&data, &kapasitas);
            }

            // Simpan
            data[*jumlah_out] = dataTransaksi;
            (*jumlah_out)++;
        }
    }
    fclose(readFile);
    return data;
}

/* =======================================================
        MODUL : get_transaksi_pengeluaran
        DESKRIPSI : sebuah fungsi yang akan mengembalikan nilai dari data transaksi pengeluaran
        INPUT : variabel dengan nama jumlah_out berupa pointer 
        OUTPUT : data transaksi dari pengeluaran didapatkan dan ditampung dalam array struct Transaksi dan variabel jumlah_out memiliki nilai ukuran dari si array yang direturn
   =======================================================*/

struct Transaksi *get_transaksi_pengeluaran(int *jumlah_out){
    int kapasitas = 10;
    *jumlah_out = 0;
    char line[150];
    struct Transaksi dataTransaksi;
    struct Transaksi *data = malloc(kapasitas * sizeof(struct Transaksi));
    if (!data) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(data);
        return NULL;
    }
    while (fgets(line, sizeof(line), readFile)) {

        if (sscanf(line, "%9[^|]|%19[^|]|%49[^|]|%19[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) != 6) {
            continue;
        }

        if (strcmp(dataTransaksi.jenis, "Pengeluaran") == 0) {

            // Perlu perbesar kapasitas
            if (*jumlah_out == kapasitas) {
                tambah_ukuran_array_transaksi(&data, &kapasitas);
            }

            // Simpan
            data[*jumlah_out] = dataTransaksi;
            (*jumlah_out)++;
        }
    }
    fclose(readFile);
    return data;
}

/* =======================================================
        MODUL : tampilkan_riwayat_transaksi
        DESKRIPSI : modul yang berfungsi untuk menampilkan data riwayat transaksi berupa table
        INITIAL STATE : table yang menampilkan data riwayat transaksi belum tampil
        FINAL STATE : table yang menampilkan data riwayat transaksi sudah tampil di layar
   =======================================================*/

void tampilkan_riwayat_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

/* =======================================================
        MODUL : tampilkan_riwayat_pemasukan_transaksi
        DESKRIPSI : modul yang berfungsi untuk menampilkan data riwayat transaksi dengan jenis pemasukan berupa table
        INITIAL STATE : table yang menampilkan data riwayat transaksi dengan jenis pemasukan belum tampil
        FINAL STATE : table yang menampilkan data riwayat transaksi dengan jenis pemasukan sudah tampil di layar
   =======================================================*/

void tampilkan_riwayat_pemasukan_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi_pemasukan(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

/* =======================================================
        MODUL : tampilkan_riwayat_pengeluaran_transaksi
        DESKRIPSI : modul yang berfungsi untuk menampilkan data riwayat transaksi dengan jenis pengeluaran berupa table
        INITIAL STATE : table yang menampilkan data riwayat transaksi dengan jenis pengeluaran belum tampil
        FINAL STATE : table yang menampilkan data riwayat transaksi dengan jenis pengeluaran sudah tampil di layar
   =======================================================*/

void tampilkan_riwayat_pengeluaran_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi_pengeluaran(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

/* =======================================================
        MODUL : menu_riwayat_transaksi
        DESKRIPSI : menampilkan menu yang memberikan pilihan kepada user untuk memilih apakah ingin menampilkan seluruh riwayat transaksi, hanya pengeluaran, atau hanya pemasukan
        INITIAL STATE : user belum memilih ingin menampilkan riwayat transaksi apa
        FINAL STATE : user sudah memilih ingin menampilkan riwayat transaksi apa
   =======================================================*/

void menu_riwayat_transaksi(){
    int navigasi;
    bool menu_transaksi = true;
    bool alert = false;
  while (menu_transaksi) {
    clearScreen();
    header();
    tampilan_menu_riwayat_transaksi();
    if (alert) {
            printf("\nMohon Pilih menu hanya (0-3): ");
        }
        alert = false;
        scanf("%d", &navigasi);
        getchar();
        switch (navigasi) {
            case 0:
              menu_transaksi = false;
            break;
            case 1:
              tampilkan_riwayat_transaksi();
            break;
            case 2:
              tampilkan_riwayat_pemasukan_transaksi();
            break;
            case 3:
              tampilkan_riwayat_pengeluaran_transaksi();
            break;
            default:
                alert = true;
            break;
        }
  }
}