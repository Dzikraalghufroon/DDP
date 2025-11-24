#include <stdio.h>
#include <stdlib.h>

struct PosAnggaran {
  char pos[50];
  long batas_nominal;
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
        printf("| %-4d | %-30s | %16.2ld |\n", i + 1, arr[i].pos, arr[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

}

void masukkan_nominal(long *nominal){
    printf("Masukkan nominal: ");
    scanf("%ld", nominal);
    getchar();
}

void footer_line(){
    printf("==================================================================="
            "==================================================================="
            "===========\n");
}


void menu_transaksi_view(){
    printf(
            "========================= MENU TRANSAKSI =========================");
        printf(" \n Pilih jenis Transaksi!\n");
        printf("     1. Pemasukan\n");
        printf("     2. Pengeluaran\n");
        printf("     0. Keluar\n");
        printf(
            "==================================================================");
        printf("\n \tPilih menu (0-2): ");
}

void input_pemasukan_view(){

        printf("\n#____________________________________________Pemasukan____________________________________________#\n");
        printf("\n+-Silahkan input nominal dari Pemasukan anda-+\n\n");
        printf("+-Pemasukan harus bilangan positif ( >0 )-+\n");
        printf("\n#_________________________________________________________________________________________________#\n");
}

void menu_rekapitulasi(){
    printf("\nPilih Opsi untuk menampilkan transaksi\n");
    printf("1. Pemasukan dan Transaksi\n");
    printf("2. Hanya Pemasukan\n");
    printf("3. Hanya Pengeluaran\n");
    printf("0. kembali");
}

void menu_bulan(){
    printf("\nPilih bulan yang ingin ditampilkan di laporan\n");
    printf("1. Januari \t 7. Juli\n");
    printf("2. Februari\t 8. Agustus\n");
    printf("3. maret   \t 9. September\n");
    printf("4. April   \t 10. Oktober\n");
    printf("5. Mei     \t 11. November\n");
    printf("6. Juni    \t 12. Desember\n");
    printf("0. kembali");
}


void realisasi_tabel_header() {

    printf("Riwayat transaksi anda\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-12s | %-15s | %-10s | %-15s | %-30s |\n",
           "ID", "Tanggal", "Pos Anggaran", "Jenis", "Nominal (Rp)", "Deskripsi");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
void realisasi_tabel_row(struct Transaksi *t) {
    printf("| %-10s | %-12s | %-15s | %-10s | %-15.2Lf | %-30s |\n",
           t->kode,
           t->tanggal,
           t->pos,
           t->jenis,
           t->nominal,
           t->keterangan);
}

void realisasi_tabel_footer() {
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}

void realisasi_transaksi_table(struct Transaksi *data, int jumlah) {
    realisasi_tabel_header();

    for (int i = 0; i < jumlah; i++) {
        realisasi_tabel_row(&data[i]);
    }

    realisasi_tabel_footer();
}