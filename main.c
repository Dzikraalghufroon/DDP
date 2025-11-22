#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int main(){
    int navigasi;
    bool menu = true;
    while (menu) {
        // clearScreen();

        // header();

        printf(
            "=========================== MENU UTAMA ===========================");
        printf(" \n");
        printf("     1. Pencatatan Pos Anggaran\n");
        printf("     2. Pencatatan Transaksi\n");
        printf("     3. Tampilkan laporan keuangan\n");
        printf("     0. Keluar\n");
        printf(
            "==================================================================");
        printf("\n \tPilih menu (0-3): ");
        /*
            perulangan untuk navigasi 
        */
        scanf(" %d", &navigasi);
        getchar();
        switch (navigasi) {
            case 0:
            printf("____________________");
            printf("\n|Program selesai.|\n");
            menu = false;
            break;
            case 1:
            //   menu_pos_anggaran_controller();
            break;
            case 2:
            //   menu_transaksi();
            break;
            case 3:
            //  menu_analisis_controller();
            break;
            default:
            printf("Mohon Pilih menu hanya (0-5): ");
            break;
        }
        
    }
}