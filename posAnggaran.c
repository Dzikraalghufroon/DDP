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
void footer_line();
void menu_pos_anggaran_view();
void daftar_pos_anggaran_view(struct PosAnggaran arr[], int jumlah);
void masukkan_nominal(long *nominal);
void konfirmasi_penambahan_pos();
bool validasi_nominal(long nominal);
bool lanjut_tambah_pos(char var);
bool berhenti_menambah(char var);
void tambah_ukuran_array_posAnggaran(struct PosAnggaran **arr, int *kapasitas);

/* =======================================================
        MODUL : cekPos_anggaran
        DESKRIPSI : modul yang berfungsi untuk mengecek apakah data sudah ada di pos anggaran
        INPUT : string data
        OUTPUT : boolean true atau false
   =======================================================*/


bool cekPos_anggaran(const char *data){
    FILE *fp = fopen("pos_anggaran.txt", "r");
    if (!fp) return false;
    struct PosAnggaran pos;
    char line[256];
    while (fgets(line, sizeof(line),fp )) {
        if (sscanf(line, "%[^|]|%ld", pos.pos, &pos.batas_nominal) == 2) {
            if (strcmp(pos.pos, data) == 0) {
                fclose(fp);
                return true;
            }
        }
    }
    return false;
} 

/* =======================================================
        MODUL : input_pos_anggaran
        DESKRIPSI : modul agar user menginput nama dari pos anggaran
        INITIAL STATE : user belum menginput pos anggaran
        FINAL STATE : user sudah menginput pos anggaran
   =======================================================*/

void input_pos_anggaran(char *pos){
    printf("\tMasukkan Nama pos: ");
    fgets(pos, sizeof(pos), stdin);
    pos[strcspn(pos, "\n")] = '\0';
}

/* =======================================================
        MODUL : pos_anggaran_sudah_ada
        DESKRIPSI : menampilkan peringatan bahwa pos anggaran yang diinput user sudah ada
        INITIAL STATE : peringatan belum muncul
        FINAL STATE : peringatan muncul
   =======================================================*/

void pos_anggaran_sudah_ada(char *pos){
    printf("Pos '%s' sudah ada di dalam file. Silakan masukkan nama lain.\n",pos);
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
}

/* =======================================================
        MODUL : input_batas_anggaran
        DESKRIPSI : modul untuk user menginput batas anggaran
        INITIAL STATE : user belum menginput batas anggaran
        FINAL STATE : user sudah menginput batas anggaran
   =======================================================*/

void input_batas_anggaran(long *nominal){
    printf("\tMasukkan batas anggaran: ");
    scanf(" %ld", nominal);
}

/* =======================================================
        MODUL : validasi_batas_anggaran
        DESKRIPSI : menampilkan peringatan bahwa user menginput nominal tidak lebih dari 0
        INITIAL STATE : peringatan belum muncul
        FINAL STATE : peringatan muncul
   =======================================================*/

void validasi_batas_anggaran(long nominal){
    printf("Anda menetapkan batas anggaran sebesar '%ld', batas anggaran "
        "harus lebih besar dari nol.\n", nominal);
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
}

/* =======================================================
        MODUL : tanya_lanjut
        DESKRIPSI : menanyakan kepada user apakah masih ingin menambah data atau sudah selesai
        INITIAL STATE : user belum memberi jawaban
        FINAL STATE : user sudah memberi jawaban
   =======================================================*/

void tanya_lanjut(bool *mengisi){
    bool alert = false;
    char lanjut;
    while (true) {
        //menanyakan kepada user apakah masih ingin menambah data atau sudah selesai
        header();
        if (alert) {
            clearScreen();
            header();
            printf("\n mohon hanya menginput (y/n)\n");
        }
        konfirmasi_penambahan_pos();

        scanf(" %c", &lanjut);
        getchar();
        if (lanjut_tambah_pos(lanjut)) {
            break;
        } else if (berhenti_menambah(lanjut)) {
            mengisi = false;
        break;
        } else {
        alert = true;
        }
    }
}

/* =======================================================
        MODUL : getPosAnggaran
        DESKRIPSI : modul yang berfungsi untuk mengambil data dari pos anggaran
        INPUT : integer jumlahOut
        OUTPUT : array yang berisi seluruh pos anggaran 
   =======================================================*/


struct PosAnggaran *getPosAnggaran(int *jumlahOut) {
    FILE *fp = fopen("pos_anggaran.txt", "r");
    if (!fp) {
        printf("file pos anggaran tidak ditemukan\n");
        *jumlahOut = 0;
        return NULL;
    }
    int kapasitas = 50;  
    int count = 0;

    struct PosAnggaran *data = malloc(kapasitas * sizeof(struct PosAnggaran));
    if (!data) {
        fclose(fp);
        return NULL;
    }

    while (true) {
        if (count == kapasitas) {
            tambah_ukuran_array_posAnggaran(&data, &kapasitas);
            if (!data) {
                fclose(fp);
                return NULL;
            }
        }
        if (fscanf(fp, "%49[^|]|%ld\n", data[count].pos, &data[count].batas_nominal) != 2) {
            break;  
        }
        count++;
    }

    fclose(fp);
    *jumlahOut = count;
    return data;
}

/* =======================================================
        MODUL : menyimpan_pos_anggaran
        DESKRIPSI : modul untuk menyimpan pos anggaran ke file
        INITIAL STATE : data belum disimpan
        FINAL STATE : data sudah disimpan
   =======================================================*/

void menyimpan_pos_anggaran(char *nama_pos, long nominal){
    getchar();
        FILE *fp = fopen("pos_anggaran.txt", "a");
        if (!fp) {
            printf("Gagal membuka file untuk menulis!\n");
            return;
        }
        fprintf(fp, "%s|%ld\n", nama_pos, nominal);
        fclose(fp);

        printf("Data berhasil ditambahkan!\n");
}

/* =======================================================
        MODUL : edit_data_dari_file_pos_anggaran
        DESKRIPSI : mengedit data pos anggaran dari file pos_anggaran.txt
        INPUT : string namaCari
        OUTPUT : boolean true atau false
   =======================================================*/


bool edit_data_dari_file_pos_anggaran(char *namaCari){
    char nama_pos[50]; 
    long nominal; 
    bool result = false;
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !EDIT) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%ld\n", nama_pos, &nominal) == 2) {
      nama_pos[strcspn(nama_pos, "\n")] = '\0'; // hapus newline
        namaCari[strcspn(namaCari, "\n")] = '\0';
        // jika ditemukan data yang cocok maka data batas nominal yang sebelumnya
        // akan di ganti dengan yang baru
        if (strcmp(nama_pos, namaCari) == 0) {
            result = true;
            masukkan_nominal(&nominal);
        }
        // melakukan proses menulis ke sebuah file yang akan menampung data baru
        fprintf(EDIT, "%s|%ld\n", nama_pos, nominal);
    }

    fclose(fp);
    fclose(EDIT);

    // menghapus file lama untuk diganti oleh file baru
    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");
    return result;
}

/* =======================================================
        MODUL : hapus_data_dari_file_pos_anggaran
        DESKRIPSI : menghapus data pos anggaran dari file pos_anggaran.txt
        INPUT : string namaCari
        OUTPUT : boolean true atau false
   =======================================================*/


bool hapus_data_dari_file_pos_anggaran(char *namaCari){
    char nama_pos[50]; 
    long nominal; 
    bool result = false;
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *DELETE = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !DELETE) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%ld\n", nama_pos, &nominal) == 2) {
        nama_pos[strcspn(nama_pos, "\n")] = '\0'; 
        namaCari[strcspn(namaCari, "\n")] = '\0';
        // jika ditemukan data yang cocok maka data batas nominal yang sebelumnya
        // akan di ganti dengan yang baru
        if (strcmp(nama_pos, namaCari) != 0) {
            result = true;
        // melakukan proses menulis ke sebuah file yang akan menampung data baru
            fprintf(DELETE, "%s|%ld\n", nama_pos, nominal);
        }
    }

    fclose(fp);
    fclose(DELETE);

    // menghapus file lama untuk diganti oleh file baru
    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");
    return result;
}

/* =======================================================
        MODUL : tambah_pos_anggaran
        DESKRIPSI : berfungsi untuk menambah pos anggaran
        INITIAL STATE : file belum ditambah
        FINAL STATE : file sudah ditambah
   =======================================================*/

void tambah_pos_anggaran(){
    struct PosAnggaran data;

    bool mengisi = true;
    bool sudah_ada = false;

    while (mengisi) {
        clearScreen(); 
        header();
        // User melakukan input untuk nama pos
        input_pos_anggaran(data.pos);
        // Periksa apakah pos sudah ada di file
        sudah_ada = cekPos_anggaran(data.pos);
        if (sudah_ada) {
            pos_anggaran_sudah_ada(data.pos);
            continue;
        }
        
        // User melakukan input untuk batas anggaran
        
        input_batas_anggaran(&data.batas_nominal);
        //memeriksa apakah nominal kurang atau sama dengan 0
        if (!validasi_nominal(data.batas_nominal)) { 
            //memanggil modul yang akan menampilkan peringatan bahwa nominal harus lebih besar dari 0
                validasi_batas_anggaran(data.batas_nominal);
                continue;
            }
        
        //   menyimpan data ke dalam file pos_anggaran.txt
        menyimpan_pos_anggaran(data.pos, data.batas_nominal);
        clearScreen(); 

        // memanggil procedure yang berisi perulangan untuk memvalidasi jawaban apakah user
        // masih ingin menambah data
        tanya_lanjut(&mengisi);
    }
}

/* =======================================================
        MODUL : edit_pos_anggaran
        DESKRIPSI : berfungsi untuk mengedit pos anggaran
        INITIAL STATE : file belum diedit
        FINAL STATE : file sudah diedit
   =======================================================*/

void edit_pos_anggaran(){
    char namaPos[50];
    bool success = false;
    int jumlahPos = 0;
    struct PosAnggaran *daftarPosAnggaran = getPosAnggaran(&jumlahPos);
    clearScreen();
    header();

    daftar_pos_anggaran_view(daftarPosAnggaran, jumlahPos);

    printf("Masukkan nama pos yang nominalnya ingin diubah: ");
    fgets(namaPos, sizeof(namaPos), stdin);
    namaPos[strcspn(namaPos, "\n")] = '\0';

    success = edit_data_dari_file_pos_anggaran(namaPos);
    if (success) {
      printf("\nData berhasil diubah!\n");
    } else {
      printf("\nData tidak ditemukan!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
    free(daftarPosAnggaran);
}

/* =======================================================
        MODUL : hapus_pos_anggaran
        DESKRIPSI : berfungsi untuk menghapus pos anggaran
        INITIAL STATE : file belum dihapus
        FINAL STATE : file sudah dihapus
   =======================================================*/

void hapus_pos_anggaran(){
    char namaPos[50];
    bool success = false;
    int jumlahPos = 0;
    struct PosAnggaran *daftarPosAnggaran = getPosAnggaran(&jumlahPos);
    clearScreen();
    header();

    daftar_pos_anggaran_view(daftarPosAnggaran, jumlahPos);

    printf("Masukkan nama pos yang ingin dihapus: ");
    fgets(namaPos, sizeof(namaPos), stdin);
    namaPos[strcspn(namaPos, "\n")] = '\0';

    success = hapus_data_dari_file_pos_anggaran(namaPos);
    if (success) {
      printf("\nData berhasil dihapus!\n");
    } else {
      printf("\nData tidak ditemukan!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
    free(daftarPosAnggaran);
}

/* =======================================================
        MODUL : menu_pos_anggaran
        DESKRIPSI : berisi menu dari fitur pos anggaran
        INITIAL STATE : user belum memilih
        FINAL STATE : user sudah memilih
   =======================================================*/
void menu_pos_anggaran() {
    bool menu = true;
    int navigasi;
    while (menu) {
        clearScreen();
        header();

        menu_pos_anggaran_view();

        scanf("%d", &navigasi);
        getchar();

        switch (navigasi) {
        case 0:
            menu = false;
            break;

        case 1:
            tambah_pos_anggaran();
            break;

        case 2:
            edit_pos_anggaran();
            break;

        case 3:
            hapus_pos_anggaran();
            break;

        default:
            printf("Mohon Pilih menu hanya (0-3)\n");
            getchar();
            break;
        }
    }
}
