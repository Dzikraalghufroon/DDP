#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

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

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

bool file_tidak_ada_atau_kosong (const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    //jika file tidak ada return true
    if (!fp) return true;
    int c = fgetc(fp);
    fclose(fp);
    //jika karakter pertama kosong return true
    return (c == EOF);
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/
char *getTanggal() {
    static char buffer[11]; 
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    sprintf(buffer, "%02d/%02d/%04d",
            now->tm_mday,
            now->tm_mon + 1,
            now->tm_year + 1900);

    return buffer;
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

bool validasi_nominal(long nominal){
    if (nominal <= 0) {
    return false;
    }
    return true;
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

int array_length(){
    return 0;
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

bool lanjut_tambah_pos(char var){
    if (var == 'y' || var == 'Y') {
        return true;
    }
    return false;
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

bool berhenti_menambah(char var){
    if (var == 'n' || var == 'N') {
        return true;
    }
    return false;
}

/* =======================================================
        MODUL : 
        DESKRIPSI : 
        INPUT :
        OUTPUT :
   =======================================================*/

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

void tambah_ukuran_array_integer(int **arr, int *kapasitas){
    int kapasitas_baru = (*kapasitas) * 2;

    int *temp = realloc(*arr, kapasitas_baru * sizeof(int));

    if(!temp){
        free(*arr);
        *arr = NULL;
        return;
    }
    *arr = temp;
    *kapasitas = kapasitas_baru;
}

void trim(char *s) {
    // trim leading
    char *p = s;
    while (isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p)+1);

    // trim trailing
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';
}