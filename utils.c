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
        MODUL : file_tidak_ada_atau_kosong
        DESKRIPSI : untuk memeriksa apakah file tidak ada atau masih kosong
        INPUT : string nama file
        OUTPUT : boolean true atau false
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
        MODUL : getTanggal
        DESKRIPSI : untuk mendapatkan tanggal saat program dijalankan
        INPUT : -
        OUTPUT : string berupa tanggal 
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
        MODUL : validasi_nominal
        DESKRIPSI : untuk memvalidasi apakah nominal yang diinput besar dari nol
        INPUT : long nominal
        OUTPUT : boolean true atau false
   =======================================================*/

bool validasi_nominal(long nominal){
    if (nominal <= 0) {
    return false;
    }
    return true;
}

/* =======================================================
        MODUL : lanjut_tambah_pos
        DESKRIPSI : untuk memvalidasi perintah dari user apakah tetap ingin lanjut menambah pos anggaran
        INPUT : char bernama var
        OUTPUT : boolean true atau false
   =======================================================*/

bool lanjut_tambah_pos(char var){
    if (var == 'y' || var == 'Y') {
        return true;
    }
    return false;
}

/* =======================================================
        MODUL : berhenti_menambah
        DESKRIPSI : untuk memvalidasi jawaban dari user apakah ingin berhenti untuk menambah pos anggaran
        INPUT : char bernama var
        OUTPUT : boolean true atau false
   =======================================================*/

bool berhenti_menambah(char var){
    if (var == 'n' || var == 'N') {
        return true;
    }
    return false;
}

/* =======================================================
        MODUL : tambah_ukuran_array_posAnggaran
        DESKRIPSI : untuk melakuan realloc pada sebuah array dengan tipe data struck PosAnggaran,
                    yang berfungsi agar panjang array bertambah dengan X2 ukuran array saat ini
        INITIAL STATE : array bertipe data struct PosAnggaran penuh, kapasitas masih yang lama 
        FINAL STATE : array bertipe data struct PosAnggaran sudah bertambah dua kali lipat, kapasitas sudah 
                        berukuran 2X lipat
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

/* =======================================================
        MODUL : tambah_ukuran_array_transaksi
        DESKRIPSI : untuk melakuan realloc pada sebuah array dengan tipe data struck Transaksi,
                    yang berfungsi agar panjang array bertambah dengan X2 ukuran array saat ini
        INITIAL STATE : array bertipe data struct Transaksi penuh, kapasitas masih yang lama 
        FINAL STATE : array bertipe data struct Transaksi sudah bertambah dua kali lipat, kapasitas sudah 
                        berukuran 2X lipat
   =======================================================*/

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

/* =======================================================
        MODUL : tambah_ukuran_array_integer
        DESKRIPSI : untuk melakuan realloc pada sebuah array dengan tipe data integer,
                    yang berfungsi agar panjang array bertambah dengan X2 ukuran array saat ini
        INITIAL STATE : array bertipe data struct integer penuh, kapasitas masih yang lama 
        FINAL STATE : array bertipe data struct integer sudah bertambah dua kali lipat, kapasitas sudah 
                        berukuran 2X lipat
   =======================================================*/

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


void readFile(char *namaFile){
    
}