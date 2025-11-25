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

void menu_tahun(int *tahun_array, int jumlah_tahun){
    printf("\nPilih tahun yang ingin ditampilkan di laporan\n");
    for (int i = 0; i < jumlah_tahun; i++) {
        printf("%d\n", tahun_array[i]);
    }
    printf("0. kembali");

    printf("\n \tPilih tahun (contoh :2020): ");
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


void laporan_keuangan_header(long pemasukan_total,long pengeluaran_total,long saldo, long spending_average, int jumlah_pemasukan, int jumlah_pengeluaran, char *bulan){
    printf("|================================LAPORAN KEUANGAN BULAN %s ==================================|\n", bulan);
    printf("total pemasukan (%d Transaksi)                : %ld \n",jumlah_pemasukan, pemasukan_total);
    printf("total pengeluaran (%d Transaksi)              : %ld \n",jumlah_pengeluaran, pengeluaran_total);
    printf("Saldo Akhir                                   : %ld \n", saldo);
    printf("Rata-rata pengeluaran                         : %ld \n", spending_average);
    printf("\n|==================================================================================================|\n");
}

void laporan_keuangan_body(struct RekapPengeluaran *data, int jumlah) {
    printf("POS ANGGARAN\n");
    printf("Pos             | Batas (Rp)          | Realisasi         | Sisa (Rp)       | Jumlah transaksi | Status\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%-15s | %-18.0Lf | %-16.0Lf | %-15.0Lf | %-17d | %-10s\n",
            data[i].pos,
            data[i].nominal,
            data[i].realisasi,
            data[i].sisa,
            data[i].jumlah_transaksi,
            data[i].status
        );
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");
}

void laporan_keuangan_footer(char *kondisi, float sisa_dari_pemasukan){
    printf("Kondisi Keuangan   : %s (Sisa %f%% dari total pemasukan)\n",kondisi, sisa_dari_pemasukan);
    printf("Kesimpulan         :   ");
    if (sisa_dari_pemasukan > 25) {
        printf("Anda termasuk mahasiswa hemat dan produktif.");
    }
    else if (sisa_dari_pemasukan >= 1 && sisa_dari_pemasukan <= 25) {
        printf("Keuangan Anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.");
    }
    else if (sisa_dari_pemasukan > (-10)) {
        printf("Anda mulai boros, perhatikan pengeluaran harian.");
    }
    else {
        printf("Kondisi keuangan kurang sehat. Kurangi pengeluaran dan cari tambahan pemasukan.");
    }
    printf("\n==============================================================================================================\n");
    printf("Tekan Enter untuk selesai");
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
