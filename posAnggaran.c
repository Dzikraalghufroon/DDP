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
void konfirmasi_penambahan_pos();
bool validasi_nominal(long nominal);
bool lanjut_tambah_pos(char var);
bool berhenti_menambah(char var);

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

void tambah_pos_anggaran(){
    struct PosAnggaran data;

    bool mengisi = true;
    char lanjut;
    bool alert = false;
    bool sudah_ada = false;

    while (mengisi) {
        clearScreen(); 
        header();
        // User melakukan input untuk nama pos
        printf("\tMasukkan Nama pos: ");
        fgets(data.pos, sizeof(data.pos), stdin);
        data.pos[strcspn(data.pos, "\n")] = '\0'; // hapus newline

        // Periksa apakah pos sudah ada di file
        
        sudah_ada = cekPos_anggaran(data.pos);
        if (sudah_ada) {
            printf("Pos '%s' sudah ada di dalam file. Silakan masukkan nama lain.\n",
                data.pos);
            printf("Tekan ENTER untuk melanjutkan...");
            getchar();
            continue;
        }
        
        // User melakukan input untuk batas anggaran
        
        printf("\tMasukkan batas anggaran: ");
        scanf(" %ld", &data.batas_nominal);
        getchar();
        if (!validasi_nominal(data.batas_nominal)) { 
                printf("Anda menetapkan batas anggaran sebesar '%ld', batas anggaran "
                "harus lebih besar dari nol.\n", data.batas_nominal);
                printf("Tekan ENTER untuk melanjutkan...");
                getchar();
                continue;
            }
        
        //   menyimpan data ke dalam file pos_anggaran.txt
        menyimpan_pos_anggaran(data.pos, data.batas_nominal);
        clearScreen(); 

        // perulangan untuk memvalidasi jawaban
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
            mengisi = false;
            break;
            } else if (berhenti_menambah(lanjut)) {
            break;
            } else {
            alert = true;
            }
        }
    }
}

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
            // edit_pos_anggaran_controller();
            break;

        case 3:
            // hapus_pos_anggaran_controller();
            break;

        default:
            printf("Mohon Pilih menu hanya (0-3)\n");
            getchar();
            break;
        }
    }
}