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
void menu_rekapitulasi();
void menu_bulan();
void menu_tahun(int *tahun_array, int jumlah_tahun);
void laporan_keuangan_header(long pemasukan_total,long pengeluaran_total,long saldo, long spending_average, int jumlah_pemasukan, int jumlah_pengeluaran, char *bulan);
void laporan_keuangan_body(struct RekapPengeluaran *data, int jumlah);
void laporan_keuangan_footer(char *kondisi, float sisa_dari_pemasukan);

void realisasi_transaksi_table(struct Transaksi *data, int jumlah);
void tambah_ukuran_array_transaksi(struct Transaksi **arr, int *kapasitas);
void tambah_ukuran_array_integer(int **arr, int *kapasitas);
void tambah_ukuran_array_posAnggaran(struct PosAnggaran **arr, int *kapasitas);

char *nama_bulan(int bulan){
    switch (bulan) {
        case 1:
            return "JANUARI";
        case 2:
            return "FEBRUARI";
        case 3:
            return "MARET";
        case 4:
            return "APRIL";
        case 5:
            return "MEI";
        case 6:
            return "JUNI";
        case 7:
            return "JULI";
        case 8:
            return "AGUSTUS";
        case 9:
            return "SEPTEMBER";
        case 10:
            return "OKTOBER";
        case 11:
            return "NOVEMBER";
        case 12:
            return "DESEMBER";
        default:
            return ""; 
    }
}

int filter_bulan(char *tanggal){
    int d, m, y;
        if (sscanf(tanggal, "%d/%d/%d", &d, &m, &y) == 3) {
        return m;
        }
        return 0;
}

int filter_tahun(char *tanggal){
    int d, m, y;
        if (sscanf(tanggal, "%d/%d/%d", &d, &m, &y) == 3) {
        return y;
        }
        return 0;
}

bool cek_tahun_sudah_ada(int *tahun_list, int jumlah, int tahun){
    for (int i = 0; i < jumlah; i++) {
            if (tahun_list[i] == tahun) {
                return true;
                break;
            }
        }
    return false;
}

int *data_tahun_dari_transaksi(int *jumlah_tahun_out) {
    int kapasitas = 10;
    int *tahun_list = malloc(kapasitas * sizeof(int));
    if (!tahun_list) {
        printf("Gagal mengalokasikan memori untuk tahun_list!\n");
        return NULL;
    }

    *jumlah_tahun_out = 0;

    char line[200];
    char tanggal[20];

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(tahun_list);
        return NULL;
    }

    while (fgets(line, sizeof(line), readFile)) {

        // Ambil hanya tanggal dari file (pastikan format sesuai)
        if (sscanf(line, "%*49[^|]|%19[^|]|%*49[^|]|%*49[^|]|%*ld|%*99[^\n]", 
                   tanggal) != 1) {
            continue;
        }

        int y = filter_tahun(tanggal); 
        if (y == 0) continue; // invalid

        // --- Cek apakah tahun y sudah ada dalam array ---
        bool sudah_ada = cek_tahun_sudah_ada(tahun_list, *jumlah_tahun_out, y);
        

        if (!sudah_ada) {
            // Jika array penuh resize
            if (*jumlah_tahun_out == kapasitas) {
                tambah_ukuran_array_integer(&tahun_list, &kapasitas);
            }

            tahun_list[*jumlah_tahun_out] = y;
            (*jumlah_tahun_out)++;
        }
    }

    fclose(readFile);

    return tahun_list; // berisi array tahun unik
}

struct Transaksi *getPemasukan(int *jumlah_out, int target_bulan){
    int kapasitas = 10;
    *jumlah_out = 0;
    char line[150];
    struct Transaksi dataTransaksi;
    struct Transaksi *data = malloc(kapasitas * sizeof(struct Transaksi));
    if (!data) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(data);
        return NULL;
    }
    while (fgets(line, sizeof(line), readFile)) {

        if (sscanf(line, "%9[^|]|%19[^|]|%49[^|]|%19[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) != 6) {
            continue;
        }

        // Filter jenis + bulan
        int m = filter_bulan(dataTransaksi.tanggal);
        if (strcmp(dataTransaksi.jenis, "Pemasukan") == 0 && m == target_bulan) {

            // Perlu perbesar kapasitas
            if (*jumlah_out == kapasitas) {
                tambah_ukuran_array_transaksi(&data, &kapasitas);
            }

            // Simpan
            data[*jumlah_out] = dataTransaksi;
            (*jumlah_out)++;
        }
    }
    fclose(readFile);
    return data;
}

struct Transaksi *getPengeluaran(int *jumlah_out,int target_bulan){
    int kapasitas = 10;
    *jumlah_out = 0;
    char line[150];
    struct Transaksi dataTransaksi;
    struct Transaksi *data = malloc(kapasitas * sizeof(struct Transaksi));
    if (!data) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(data);
        return NULL;
    }
    while (fgets(line, sizeof(line), readFile)) {

        if (sscanf(line, "%9[^|]|%19[^|]|%49[^|]|%19[^|]|%ld|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) != 6) {
            continue;
        }

        // Filter jenis + bulan
        int m = filter_bulan(dataTransaksi.tanggal);
        if (strcmp(dataTransaksi.jenis, "Pengeluaran") == 0 && m == target_bulan) {

            // Perlu perbesar kapasitas
            if (*jumlah_out == kapasitas) {
                tambah_ukuran_array_transaksi(&data, &kapasitas);
            }

            // Simpan
            data[*jumlah_out] = dataTransaksi;
            (*jumlah_out)++;
        }
    }
    fclose(readFile);
    return data;
}
char *kondisi_keuangan(int saldo){
    static char kondisi[9]; 
    if (saldo < 0) {
        strcpy(kondisi, "Defisit");
    }
    else if (saldo == 0) {
        strcpy( kondisi ,"Seimbang");
    }
    else {
        strcpy( kondisi ,"Surplus");
    }
    return kondisi;
}

long pemasukan_total(int *jumlah_data_out,int target_bulan){
    int jumlah_data =0;
    long total = 0;
    struct Transaksi *Pemasukan = getPemasukan(&jumlah_data, target_bulan);
    if (Pemasukan) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pemasukan[i].nominal;
        }
// membebaskan memori di heap
        free(Pemasukan);
    }
//jika butuh jumlah data maka diisi
    if (jumlah_data_out != NULL) { 
        *jumlah_data_out = jumlah_data;
    }
    return total;
}

long pengeluaran_total(int *jumlah_data_out,int target_bulan){
    int jumlah_data = 0;
    long total = 0;
    struct Transaksi *Pengeluaran = getPengeluaran(&jumlah_data,target_bulan);
    if (Pengeluaran) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pengeluaran[i].nominal;
        }
// membebaskan memori di heap
        free(Pengeluaran);
    }
//jika butuh jumlah data maka diisi
    if (jumlah_data_out != NULL) { 
        *jumlah_data_out = jumlah_data;
    }
    return total;
}

int hitung_jumlah_transaksi_pengeluaran(){
    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        return 0;
    }
    int count = 0;
    char line[150];
    char jenis[50];

    while (fgets(line, sizeof(line), readFile)) {
    if (sscanf(line, "%*9[^|]|%*19[^|]|%*49[^|]|%19[^|]|%*ld|%*49[^\n]", jenis) == 1) {
        if (strcmp(jenis, "Pengeluaran") == 0)
            count++;
    }
}

    fclose(readFile);
    return count;
}

long calculate_saldo(int target_bulan) {
  long income = pemasukan_total(NULL,target_bulan);
  long spending = pengeluaran_total(NULL,target_bulan);
  return income - spending;
}


bool pengeluaran_rataRata(long params){
    if (params > 0) {
    return true;
    }
    return false;    
}
long kalkulasi_pengeluaran_rataRata(int target_bulan){
    long saldo= calculate_saldo(target_bulan);
   if (pengeluaran_rataRata(saldo)) {
    return pengeluaran_total(NULL,target_bulan)/hitung_jumlah_transaksi_pengeluaran();
   } 
   return 0;
}

float persentase_dari_sisa_total_pemasukan(long saldo, long pemasukan){
    if (pemasukan == 0) {
        return -1; //menandai bahwa error 
    }
    return ((float)saldo / (float)pemasukan) * 100.0f;
}

void Laporan_keuangan(int bulan){
    int jumlah_transaksi_pemasukan;
    int jumlah_transaksi_pengeluaran;
    int jumlah_data_pemasukan;
    int jumlah_data_pengeluaran;

    long saldo_akhir = calculate_saldo(bulan);
    long total_pemasukan = pemasukan_total(&jumlah_transaksi_pemasukan,bulan);
    long total_pengeluaran = pengeluaran_total(&jumlah_transaksi_pengeluaran, bulan);
    float persentase_dari_sisa_pemasukan = persentase_dari_sisa_total_pemasukan(saldo_akhir,total_pemasukan);

    struct Transaksi *Pengeluaran = getPengeluaran(&jumlah_data_pengeluaran,bulan);
    struct Transaksi *Pemasukan = getPemasukan(&jumlah_data_pemasukan, bulan);

    char kondisi_keuangan_mahasiswa[10];
    strcpy(kondisi_keuangan_mahasiswa, kondisi_keuangan( saldo_akhir));

    clearScreen();
    header();
    laporan_keuangan_header(total_pemasukan, total_pengeluaran, saldo_akhir, kalkulasi_pengeluaran_rataRata(bulan),jumlah_transaksi_pemasukan,jumlah_transaksi_pengeluaran,nama_bulan(bulan));

    getchar();
    free(Pengeluaran);
    free(Pemasukan);
}

void menu_utama_rekapitulasi(){
    bool menu = true;
  int navigasi_bulan;
  int navigasi_tahun;
  int jumlah_tahun;
    int *tahun_array = data_tahun_dari_transaksi(&jumlah_tahun);
    
  while (menu) {
    clearScreen();
    header();

    menu_tahun(tahun_array, jumlah_tahun);
    scanf("%d", &navigasi_tahun);
    getchar();

    free(tahun_array);

    menu_bulan();
    printf("\n \tPilih bulan (0-12): ");

    scanf("%d", &navigasi_bulan);
    getchar();

    switch (navigasi_bulan) {
    case 0:
        menu = false;
        break;

    case 1:
        // analisis_keuangan_controller_main(1);
        break;

    case 2:
        // analisis_keuangan_controller_main(2);
        break;

    case 3:
        // analisis_keuangan_controller_main(3);
        break;

    case 4:
        // analisis_keuangan_controller_main(3);
        break;
    case 5:
        // analisis_keuangan_controller_main(3);
        break;
    case 6:
        // analisis_keuangan_controller_main(3);
        break;
    case 7:
        // analisis_keuangan_controller_main(3);
        break;
    case 8:
        // analisis_keuangan_controller_main(3);
        break;
    case 9:
        // analisis_keuangan_controller_main(3);
        break;
    case 10:
        // analisis_keuangan_controller_main(3);
        break;
    case 11:
        Laporan_keuangan(navigasi_bulan);
        menu =  false;
        break;
    case 12:
        // analisis_keuangan_controller_main(3);
        break;
    default:
        printf("Mohon Pilih menu hanya (0-3)\n");
        getchar();
        break;
    }
}
}