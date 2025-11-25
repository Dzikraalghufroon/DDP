#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void clearScreen();
void header();
void menu_pos_anggaran();
void menu_utama();
void menu_transaksi();
void menu_utama_rekapitulasi();

int main(){
    int navigasi;
    bool menu = true;
    bool alert = false;
    while (menu) {

        clearScreen();
        header();
        menu_utama();

        if (alert) {
            printf("\nMohon Pilih menu hanya (0-3): ");
        }
        alert = false;
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
              menu_transaksi();
            break;
            case 3:
                menu_utama_rekapitulasi();
            break;
            default:
                alert = true;
            break;
        }
        
    }
}