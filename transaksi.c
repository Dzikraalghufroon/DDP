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
void menu_transaksi_view();
void input_pemasukan_view();
void daftar_pos_anggaran_view(struct PosAnggaran arr[], int jumlah);
bool cekPos_anggaran(const char *data);
bool file_tidak_ada_atau_kosong (const char *namaFile);
bool validasi_nominal(long nominal);
struct PosAnggaran *getPosAnggaran(int *jumlahOut);
char *getTanggal();

/* =======================================================
        MODUL : buat_file_transaksi
        DESKRIPSI : modul yang berfungsi untuk membuat file data_transaksi.txt
        INITIAL STATE : file data_transaksi.txt belum ada
        FINAL STATE : file data_transaksi.txt sudah ada
   =======================================================*/

void buat_file_transaksi(){
    FILE *BuatFile = fopen("data_transaksi.txt", "a");
    fclose(BuatFile);
}

/* =======================================================
        MODUL : getId_transaksi
        DESKRIPSI : berfungsi sebagai generate id dari data transaksi
        INPUT : - 
        OUTPUT : char dengan nilai berupa id baru yang di hasilkan dengan formula:
                id terakhir + 1 
   =======================================================*/

char *getId_transaksi() {
    FILE *fp = fopen("data_transaksi.txt", "r");
    static char id[10];
    char line[100];
    char id_terakhir[10] = "T000"; // T000 sebagai default
    int nomor; // mengambil angka di belakang huruf T

    if (!fp) {
        sprintf(id, "T001");
        return id;
    }

    // Untuk membaca semua file sampai akhir agar bisa mendapatkan id terakhir
    while (fgets(line, sizeof(line), fp)) {
        // Ambil bagian id sebelum '|' untuk menghasilkan id baru
        line[strcspn(line, "\n")] = '\0'; // hapus newline
        sscanf(line, "%9[^|]", id_terakhir); // ambil ID sebelum |
    }
    fclose(fp);

    sscanf(id_terakhir + 1, "%d", &nomor);
    // artinya kita mengambil array 1 sampai seterusnya dan mengabaikan indeks ke
    // 0
    nomor++;

    // Bentuk ulang ID baru dengan format T001, T002, dst.
    sprintf(id, "T%03d", nomor);
    return id;
}

/* =======================================================
        MODUL : input_pos
        DESKRIPSI : modul untuk user menginput pos anggaran
        INITIAL STATE : string pos masih belum bernilai
        FINAL STATE : string pos sudah memiliki nilai karena user telah memberi input
   =======================================================*/

void input_pos(char *pos){
    while (true) {
        printf("Masukkan Pos Anggaran : ");
        fgets(pos, sizeof(pos), stdin);
        pos[strcspn(pos, "\n")] = '\0';
        getchar();
        if (cekPos_anggaran(pos)) { // valid
            break;
        } else {
            printf("\nPos Anggaran harus berasal dari data pos anggaran yang diinputkan\n");
        }
    }

}

/* =======================================================
        MODUL : input_nominal
        DESKRIPSI : modul untuk user menginput nominal
        INITIAL STATE : long nominal masih belum memiliki nilai
        FINAL STATE : long nominal sudah memiliki nilai
   =======================================================*/

void input_nominal(long *nominal){
    while (true) {
        printf("\nMasukkan nominal : ");
        scanf("%ld", nominal);
        getchar();
        // while (getchar() != '\n');
        if (validasi_nominal(*nominal)) {
            break;
        }
        else {
            printf("Nominal harus bilangan positif (>0).\n");
        }
    }
}

/* =======================================================
        MODUL : input_deskripsi
        DESKRIPSI : modul untuk user menginput deskripsi dari transaksi
        INITIAL STATE : string deskripsi masih belum memiliki nilai
        FINAL STATE : string deskripsi sudah memiliki nilai
   =======================================================*/

void input_deskripsi(char *deskripsi){
    printf("Masukkan deskripsi : ");
    fgets(deskripsi, sizeof(deskripsi), stdin);
    deskripsi[strcspn(deskripsi, "\n")] = '\0'; 
}

/* =======================================================
        MODUL : tambah_transaksi_pemasukan
        DESKRIPSI : untuk menyimpan data dari transaksi dengan jenis pemasukan kedalam file data_transaksi.txt
        INITIAL STATE : data di file data_transaksi.txt belum bertambah / masih belum ada perubahan dari sebelumnya
        FINAL STATE : data di file data_transaksi.txt sudah bertambah dengan jenis Pemasukan
   =======================================================*/

void tambah_transaksi_pemasukan(char *kode_transaksi,char * tanggal,long nominal,char *deskripsi){
    FILE *fwrite = fopen("data_transaksi.txt", "a");
    
    //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
    fprintf(fwrite, "%s|%s|%s|%s|%ld|%s\n", kode_transaksi, tanggal,"Pemasukan","Pemasukan",nominal,deskripsi);
    fclose(fwrite);
}


/* =======================================================
        MODUL : tambah_transaksi_pengeluaran
        DESKRIPSI : untuk menyimpan data dari transaksi dengan jenis pengeluaran kedalam file data_transaksi.txt
        INITIAL STATE : data di file data_transaksi.txt belum bertambah / masih belum ada perubahan
        FINAL STATE : data di file data_transaksi.txt sudah bertambah dengan jenis pengeluaran
   =======================================================*/

void tambah_transaksi_pengeluaran(char *kode_transaksi,char * tanggal,char *pos,long nominal,char *deskripsi){
    FILE *fwrite = fopen("data_transaksi.txt", "a");
    
    //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
    fprintf(fwrite, "%s|%s|%s|%s|%ld|%s\n", kode_transaksi, tanggal,pos,"Pengeluaran",nominal,deskripsi);
    fclose(fwrite);
}

/* =======================================================
        MODUL : transaksi_pemasukan
        DESKRIPSI : modul yang menghimpun modul lainnya yang berfungsi, agar user bisa melakukan input transaksi pemasukan
        INITIAL STATE : user belum melakukan input transaksi berupa pemasukan
        FINAL STATE : user sudah melakukan input transaksi berupa pemasukan, sehingga data di file data_transaksi.txt bertambah
   =======================================================*/

void transaksi_pemasukan(){
    struct Transaksi data;
    clearScreen();
    header();
    input_pemasukan_view();
    input_nominal(&data.nominal);
    input_deskripsi(data.keterangan);

    tambah_transaksi_pemasukan(getId_transaksi(), getTanggal(), data.nominal, data.keterangan);
    clearScreen();
}

/* =======================================================
        MODUL : transaksi_pengeluaran
        DESKRIPSI : modul yang menghimpun modul lainnya yang berfungsi, agar user bisa melakukan input transaksi pengeluaran
        INITIAL STATE : user belum melakukan input transaksi berupa pengeluran
        FINAL STATE : user sudah melakukan input transaksi berupa pengeluaran, sehingga data di file data_transaksi.txt bertambah
   =======================================================*/

void transaksi_pengeluaran(){
    int jumlahPos = 0;
    struct PosAnggaran *daftarPosAnggaran = getPosAnggaran(&jumlahPos);
    struct Transaksi data;

    clearScreen();
    header();
    daftar_pos_anggaran_view(daftarPosAnggaran, jumlahPos);
    input_pemasukan_view();

    input_pos(data.pos);
    input_nominal(&data.nominal);
    input_deskripsi(data.keterangan);

    tambah_transaksi_pengeluaran(getId_transaksi(), getTanggal(), data.pos, data.nominal, data.keterangan);

    free(daftarPosAnggaran);
    clearScreen();
}

/* =======================================================
        MODUL : menu transaksi
        DESKRIPSI : menu utama dari fitur tambah transaksi
        INITIAL STATE : user belum memilih ingin tambah transaksi pemasukan atau pengeluaran
        FINAL STATE : user bisa menambah transaksi berupa pengeluaran atau pemasukan
   =======================================================*/

void menu_transaksi(){
    // memanggil fungsi file_kosong untuk memeriksa apakah file tidak ada
    if (file_tidak_ada_atau_kosong("data_transaksi.txt")) {
        buat_file_transaksi();
    }
    bool menu = true;
    int navigasi;
    while (menu) {
        clearScreen();
        header();
        menu_transaksi_view();
        scanf(" %d", &navigasi);
        getchar();
        switch (navigasi) {
        // jika user input 0 maka program akan kembali ke menu utama
        case 0:
        menu = false;
        break;
        /* jika user input 2 maka program akan masuk ke menu pengeluaran*/
        case 1:
            transaksi_pemasukan();
        break;

        /* jika user input 2 maka program akan masuk ke menu pengeluaran*/
        case 2:
            transaksi_pengeluaran();
        break;

        /*Jika user menginput selain 0 - 2*/
        default:
        printf("Mohon Pilih menu hanya (0-2): ");
        break;
        }        
    }
}