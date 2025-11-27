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
        MODUL : ClearScreen()
        DESKRIPSI : Mengosongkan layar
        
   =======================================================*/

void clearScreen() {
#ifdef _WIN32           //jika menggunakan windos
    system("cls");       // mengosongkan layar
#else                   // jika menggunaka selain windos
    system("clear");    // mengosongkan layar
#endif
}

/* =======================================================
        MODUL : header
        DESKRIPSI : menampilkan tampilan header aplikasi
        
   =======================================================*/

void header() {
    printf("|==================================================================================================|\n");
    printf("|                                 APLIKASI KEUANGAN MAHASISWA                                      |\n");
    printf("|==================================================================================================|\n");
}

/* =======================================================
        MODUL : menu_utama
        DESKRIPSI : menampilkan daftar fitur-fitur utama yang ada di aplikasi
        
   =======================================================*/

void menu_utama(){
    printf("=========================== MENU UTAMA ===========================");
    printf(" \n");
    printf("     1. Pencatatan Pos Anggaran\n");
    printf("     2. Pencatatan Transaksi\n");
    printf("     3. Tampilkan laporan keuangan\n");
    printf("     4. Riwayat Transaksi\n");
    printf("     0. Keluar\n");
    printf("==================================================================");
    printf("\n \tPilih menu (0-4): ");
}


/* =======================================================
        MODUL : menu_pos_anggaran_view
        DESKRIPSI : menampilkan fitur-fitur yang tersedia di bagian pencatatan pos anggaran 
        
   =======================================================*/

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

/* =======================================================
        MODUL : konfirmasi_penambahan_pos
        DESKRIPSI : menampilkan konirmasi kepada user apakah masih ingin menambah pos anggaran atau tidak
        
   =======================================================*/

void konfirmasi_penambahan_pos(){
    printf("\tApakah anda masih ingin menambah pos anggaran? \n");
        printf("\tmasukkan (y) untuk tetap menambah \n\tmasukkan (n) jika "
              "selesai \n=");
}

/* =======================================================
        MODUL : daftar_pos_anggaran_view
        DESKRIPSI : menampilkan table dari pos anggaran yang tersedia di file pos_anggaran.txt
        INITIAL STATE : data pos anggaran untuk ditampilkan masih kosong
        FINAL STATE : seluruh pos anggaran yang ada ditampilkan ke layar
   =======================================================*/

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int jumlah){
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");
    for (int i = 0; i < jumlah; i++) {
        printf("| %-4d | %-30s | %16.2ld |\n", i + 1, arr[i].pos, arr[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

}


/* =======================================================
        MODUL : masukkan_nominal
        DESKRIPSI : meminta user untuk menginput nominal untuk disimpan
        INITIAL STATE : variabel nominal masih belum memiliki nila
        FINAL STATE : variabel nominal memiliki nilai
   =======================================================*/

void masukkan_nominal(long *nominal){
    printf("Masukkan nominal: ");
    scanf("%ld", nominal);
    getchar();
}


/* =======================================================
        MODUL : footer line
        DESKRIPSI : menampilkan garis panjang yang berfungsi sebagai footer
        
   =======================================================*/

void footer_line(){
    printf("==================================================================="
            "==================================================================="
            "===========\n");
}


/* =======================================================
        MODUL : menu_transaksi_view
        DESKRIPSI : menampilkan pilihan untuk user untuk memilih jenis transaksi, apakah pemasukan atau pengeluaran
        
   =======================================================*/

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


/* =======================================================
        MODUL : input_pemasukan_view
        DESKRIPSI : menampilkan kelayar perintah kepada user, saat ingin menginput pemasukan
        
   =======================================================*/

void input_pemasukan_view(){

        printf("\n#____________________________________________Pemasukan____________________________________________#\n");
        printf("\n+-Silahkan input nominal dari Pemasukan anda-+\n\n");
        printf("+-Pemasukan harus bilangan positif ( >0 )-+\n");
        printf("\n#_________________________________________________________________________________________________#\n");
}

/* =======================================================
        MODUL : menu_rekapitulasi
        DESKRIPSI : meminta user untuk memilih opsi dalam menampilkan riwayat transaksi apakah hanya pengeluaran
                    atau hanya pemasukan atau keduanya
        
   =======================================================*/

void menu_rekapitulasi(){
    printf("\nPilih Opsi untuk menampilkan transaksi\n");
    printf("1. Pemasukan dan Transaksi\n");
    printf("2. Hanya Pemasukan\n");
    printf("3. Hanya Pengeluaran\n");
    printf("0. kembali");
}

/* =======================================================
        MODUL : menu_tahun
        DESKRIPSI : menampilkan tahun yang tercatat dalam transaksi meminta user untuk 
                    meminta tahun berapa yang akan dilakukan untuk rekapitulasi keuangan
        INITIAL STATE : 
        FINAL STATE :
   =======================================================*/

void menu_tahun(int *tahun_array, int jumlah_tahun){
    printf("\nPilih tahun yang ingin ditampilkan di laporan\n");
    for (int i = 0; i < jumlah_tahun; i++) {
        printf("\t-%d\n", tahun_array[i]);
    }
    printf("\n__________________________________________________________________________________________________________________\n");
    printf("\t0. kembali");

    printf("\n \tPilih tahun (contoh :2020): ");
}

/* =======================================================
        MODUL : menu_bulan
        DESKRIPSI : menampilkan bulan yang akan ditampilkan dalam rekapitulasi keuangan
        
   =======================================================*/

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

/* =======================================================
        MODUL : laporan_keuangan_header
        DESKRIPSI : menampilkan info dari rekapitulasi keuangan ke layar
        INITIAL STATE : variabel pemasukan_total pengeluaran_total saldo,
                     spending_average, jumlah_pemasukan, jumlah_pengeluaran, bulan, tahun masih kosong
        FINAL STATE : variabel pemasukan_total pengeluaran_total saldo,
                     spending_average, jumlah_pemasukan, jumlah_pengeluaran, bulan, 
                     tahun sudah memiliki nilai dan menampilkan kelayar 
   =======================================================*/

void laporan_keuangan_header(long pemasukan_total,long pengeluaran_total,long saldo, long spending_average, int jumlah_pemasukan, int jumlah_pengeluaran, char *bulan, int tahun){
    printf("|================================LAPORAN KEUANGAN BULAN %s %d ==================================|\n", bulan, tahun);
    printf("total pemasukan (%d Transaksi)                : %ld \n",jumlah_pemasukan, pemasukan_total);
    printf("total pengeluaran (%d Transaksi)              : %ld \n",jumlah_pengeluaran, pengeluaran_total);
    printf("Saldo Akhir                                   : %ld \n", saldo);
    printf("Rata-rata pengeluaran                         : %ld \n", spending_average);
    printf("\n|==================================================================================================|\n");
}

/* =======================================================
        MODUL : laporan_keuangan_body
        DESKRIPSI : menampilkan table laporan keuangan kelayar 
        INITIAL STATE : pos, batas, realisasi, sisa, jumlah transaksi, dan status masih kosong
        FINAL STATE : pos, batas, realisasi, sisa, jumlah transaksi, dan status sudah memiliki nilai dan ditampilkan kelayar sebagai nilai masing masing kolom
   =======================================================*/

void laporan_keuangan_body(struct RekapPengeluaran *data, int jumlah) {
    printf("POS ANGGARAN\n");
    printf("Pos             | Batas (Rp)          | Realisasi         | Sisa (Rp)       | Jumlah transaksi | Status\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%-15s | %-18.0ld | %-16.0ld | %-15.0ld | %-17d | %-10s\n",
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

/* =======================================================
        MODUL : laporan_keuangan_footer
        DESKRIPSI : menampilkan kondisi keuangan dan kesimpulan mengenai kondisi keuangan dari user 
        INITIAL STATE : kondisi keuangan dan kesimpulan masih NULL
        FINAL STATE : kondisi keuangan dan kesimpulan sudah memiliki nilai dan ditampilkan kelayar
   =======================================================*/

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

/* =======================================================
        MODUL : realisasi_tabel_header
        DESKRIPSI : menampilkan header dari table yang akan menampilkan riwayat transaksi
        
   =======================================================*/

void realisasi_tabel_header() {

    printf("Riwayat transaksi anda\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-12s | %-15s | %-14s | %-15s | %-30s |\n",
           "ID", "Tanggal", "Pos Anggaran", "Jenis", "Nominal (Rp)", "Deskripsi");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}

/* =======================================================
        MODUL : realisasi_tabel_row
        DESKRIPSI : menampilkan nilai dari masing-masing kolom tabel riwayat transaksi
        INITIAL STATE : nilai masing-masing kolom masih kosong
        FINAL STATE : nilai masing-masing kolom sudah berisi dan ditampilkan kelayar
   =======================================================*/

void realisasi_tabel_row(struct Transaksi *t) {
    printf("| %-10s | %-12s | %-15s | %-14s | %-15.2ld | %-30s |\n",
           t->kode,
           t->tanggal,
           t->pos,
           t->jenis,
           t->nominal,
           t->keterangan);
}

/* =======================================================
        MODUL : realisasi_tabel_footer
        DESKRIPSI : menampilkan footer dari table daftar riwayat transaksi
        
   =======================================================*/

void realisasi_tabel_footer() {
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("Tekan Enter untuk selesai.....");
}

/* =======================================================
        MODUL : realisasi_transaksi_table
        DESKRIPSI : memanggil modul realisasi_tabel_header, realisasi_tabel_row, dan realisasi_tabel_footer
                    untuk disatukan dan ditampilkan kelayar
        
   =======================================================*/

void realisasi_transaksi_table(struct Transaksi *data, int jumlah) {
    clearScreen();
    realisasi_tabel_header();

    for (int i = 0; i < jumlah; i++) {
        realisasi_tabel_row(&data[i]);
    }

    realisasi_tabel_footer();
}

/* =======================================================
        MODUL : tampilan_menu_riwayat_transaksi
        DESKRIPSI : meminta user untuk memilih opsi dalam menampilkan riwayat transaksi apakah hanya pengeluaran
                    atau hanya pemasukan atau keduanya
        
   =======================================================*/

void tampilan_menu_riwayat_transaksi(){
    printf("\n=========================== MENU RIWAYAT TRANSAKSI ===========================");
    printf("\nPilih Opsi untuk menampilkan transaksi\n");
    printf("1. Pemasukan dan Transaksi\n");
    printf("2. Hanya Pemasukan\n");
    printf("3. Hanya Pengeluaran\n");
    printf("0. kembali\n");
    printf("\n==============================================================================");
    printf("\n \tPilih menu (0-3): ");
}