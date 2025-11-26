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

void tampilkan_riwayat_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

void tampilkan_riwayat_pemasukan_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi_pemasukan(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

void tampilkan_riwayat_pengeluaran_transaksi(){
  int jumlah = 0;
  struct Transaksi *data = get_transaksi_pengeluaran(&jumlah);
  realisasi_transaksi_table(data, jumlah);
  free(data);
  getchar();
}

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