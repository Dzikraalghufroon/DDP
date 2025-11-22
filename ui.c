#include <stdio.h>
#include <stdlib.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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

void header() {
    printf("|==================================================================================================|\n");
    printf("|                                 APLIKASI KEUANGAN MAHASISWA                                      |\n");
    printf("|==================================================================================================|\n");
}


