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

bool file_tidak_ada_atau_kosong (const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    //jika file tidak ada return true
    if (!fp) return true;
    int c = fgetc(fp);
    fclose(fp);
    //jika karakter pertama kosong return true
    return (c == EOF);
}

char *getTanggal() {
    static char buffer[11]; 
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    sprintf(buffer, "%02d-%02d-%04d",
            now->tm_mday,
            now->tm_mon + 1,
            now->tm_year + 1900);

    return buffer;
}

bool validasi_nominal(long nominal){
    if (nominal <= 0) {
    return false;
    }
    return true;
}

int array_length(){
    return 0;
}

bool lanjut_tambah_pos(char var){
    if (var == 'y' || var == 'Y') {
        return true;
    }
    return false;
}

bool berhenti_menambah(char var){
    if (var == 'n' || var == 'N') {
        return true;
    }
    return false;
}

void tambah_ukuran_array_posAnggaran(struct PosAnggaran **arr, int *kapasitas){
    int kapasitas_baru = (*kapasitas) * 2;

    struct PosAnggaran *temp = realloc(*arr, kapasitas_baru * sizeof(struct PosAnggaran));

    if(!temp){
        free(*arr);
        *arr = NULL;
        return;
    }
    *arr = temp;
    *kapasitas = kapasitas_baru;
}

void tambah_ukuran_array_transaksi(struct Transaksi **arr, int *kapasitas){
    int kapasitas_baru = (*kapasitas) * 2;

    struct Transaksi *temp = realloc(*arr, kapasitas_baru * sizeof(struct Transaksi));

    if(!temp){
        free(*arr);
        *arr = NULL;
        return;
    }
    *arr = temp;
    *kapasitas = kapasitas_baru;
}

