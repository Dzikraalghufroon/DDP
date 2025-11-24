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
void menu_rekapitulasi();
void realisasi_transaksi_table(struct Transaksi *data, int jumlah);
void tambah_ukuran_array_transaksi(struct Transaksi **arr, int *kapasitas);

void tambah_ukuran_array_posAnggaran(struct PosAnggaran **arr, int *kapasitas);

struct Transaksi *getPemasukan(int *jumlah_out){
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
    while (sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) == 6) {
                    if (strcmp(dataTransaksi.jenis, "Pemasukan") == 0){
                        if (*jumlah_out == kapasitas) {
                            tambah_ukuran_array_transaksi(&data, &kapasitas);
                        }
                    }
                    data[(*jumlah_out)++] = dataTransaksi;
    }
    fclose(readFile);
    return data;
}

struct Transaksi *getPengeluaran(int *jumlah_out){
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
    while (sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) == 6) {
                    if (strcmp(dataTransaksi.jenis, "Pengeluaran") == 0){
                        if (*jumlah_out == kapasitas) {
                            tambah_ukuran_array_transaksi(&data, &kapasitas);
                        }
                    }
                    data[(*jumlah_out)++] = dataTransaksi;
    }
    fclose(readFile);
    return data;
}
char *kondisi_keuangan(int saldo){
    char static kondisi[9]; 
    if (saldo < 0) {
        strcpy(kondisi, "Defisit");
    }
    else if (saldo == 0) {
        strcpy( kondisi ,"Seimbang");
    }
    else {
        strcpy( kondisi ,"Surplus");
    }
    return kondisi;
}

long pemasukan_total(int *jumlah_data_out){
    int jumlah_data;
    long total = 0;
    struct Transaksi *Pemasukan = getPemasukan(&jumlah_data);
    if (Pemasukan) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pemasukan[i].nominal;
        }
// membebaskan memori di heap
        free(Pemasukan);
    }
//jika butuh jumlah data maka diisi
    *jumlah_data_out = jumlah_data;
    return total;
}

long pengeluaran_total(int *jumlah_data_out){
    int jumlah_data;
    long total = 0;
    struct Transaksi *Pengeluaran = getPengeluaran(&jumlah_data);
    if (Pengeluaran) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pengeluaran[i].nominal;
        }
// membebaskan memori di heap
        free(Pengeluaran);
    }
//jika butuh jumlah data maka diisi
    *jumlah_data_out = jumlah_data;

    return total;
}

int hitung_jumlah_transaksi_pengeluaran(){
    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        return 0;
    }
    int count = 0;
    char line[150];
    char jenis[50];

    while (sscanf(line, "%*49[^|]|%*49[^|]|%*49[^|]|%49[^|]|%*ld|%*49[^\n]",
                   jenis) == 1) {
            if (strcmp(jenis, "Pengeluaran") == 0) {
                count++;
            }
    }
    fclose(readFile);
    return count;
}

long calculate_saldo() {
  long income = pemasukan_total(NULL);
  long spending = pengeluaran_total(NULL);
  return income - spending;
}


bool pengeluaran_rataRata(long params){
    if (params > 0) {
    return true;
    }
    return false;    
}
long kalkulasi_pengeluaran_rataRata(){
    long saldo= calculate_saldo();
   if (pengeluaran_rataRata(saldo)) {
    return pengeluaran_total(NULL)/hitung_jumlah_transaksi_pengeluaran();
   } 
   return 0;
}

void menu_rekapitulasi(){
    bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();
    header();
    menu_rekapitulasi();
    printf("\n \tPilih menu (0-3): ");

    scanf("%d", &navigasi);
    getchar();

    switch (navigasi) {
    case 0:
        menu = false;
        break;

    case 1:
        // analisis_keuangan_controller_main(1);
        break;

    case 2:
        // analisis_keuangan_controller_main(2);
        break;

    case 3:
        // analisis_keuangan_controller_main(3);
        break;

    default:
        printf("Mohon Pilih menu hanya (0-3)\n");
        getchar();
        break;
    }
}
}