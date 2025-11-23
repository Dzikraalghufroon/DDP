#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void clearScreen();
void header();
void menu_pos_anggaran();
void menu_utama();
int main(){
    int navigasi;
    bool menu = true;
    while (menu) {

        clearScreen();
        header();
        menu_utama();

        // perulangan untuk navigasi 
        scanf(" %d", &navigasi);
        getchar();
        switch (navigasi) {
            case 0:
            printf("____________________");
            printf("\n|Program selesai.|\n");
            menu = false;
            break;
            case 1:
            menu_pos_anggaran();
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