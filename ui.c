#include <stdio.h>
#include <stdlib.h>

struct PosAnggaran {
  char pos[50];
  long double batas_nominal;
};
struct Transaksi {
    char kode[10];
    char jenis[20];
    char pos[50];
    long double nominal;
    char tanggal[20];
    char keterangan[50];
};

struct RekapPengeluaran{
  char pos[50];
  long double nominal;
  long double realisasi;
  long double sisa;
  int jumlah_transaksi;
  char status[10];
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void header() {
    printf("|==================================================================================================|\n");
    printf("|                                 APLIKASI KEUANGAN MAHASISWA                                      |\n");
    printf("|==================================================================================================|\n");
}


void menu_utama(){
    printf("=========================== MENU UTAMA ===========================");
    printf(" \n");
    printf("     1. Pencatatan Pos Anggaran\n");
    printf("     2. Pencatatan Transaksi\n");
    printf("     3. Tampilkan laporan keuangan\n");
    printf("     0. Keluar\n");
    printf("==================================================================");
    printf("\n \tPilih menu (0-3): ");
}


void menu_pos_anggaran_view(){
    printf("======================= MENU POS ANGGARAN =======================");
    printf(" \n");
    printf("     1. Tambah Pos Anggaran\n");
    printf("     2. Edit Pos Anggaran\n");
    printf("     3. Hapus Pos Anggaran\n");
    printf("     0. Keluar\n");
    printf("==================================================================");
    printf("\n \tPilih menu (0-3): ");
}

void konfirmasi_penambahan_pos(){
    printf("\tApakah anda masih ingin menambah pos anggaran? \n");
        printf("\tmasukkan (y) untuk tetap menambah \n\tmasukkan (n) jika "
              "selesai \n=");
}

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int jumlah){
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");
    for (int i = 0; i < jumlah; i++) {
        printf("| %-4d | %-30s | %16.2Lf |\n", i + 1, arr[i].pos, arr[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

}

void footer_line(){
    printf("==================================================================="
            "==================================================================="
            "===========\n");
}