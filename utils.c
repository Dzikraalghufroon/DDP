#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

bool is_file_missing_or_empty(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    //jika file tidak ada return true
    if (!fp) return true;
    int c = fgetc(fp);
    fclose(fp);
    //jika karakter pertama kosong return true
    return (c == EOF);
}

char *getTanggal() {
    static char buffer[11]; 
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    sprintf(buffer, "%02d-%02d-%04d",
            now->tm_mday,
            now->tm_mon + 1,
            now->tm_year + 1900);

    return buffer;
}

bool validasi_nominal(long nominal){
    if (nominal <= 0) {
    return false;
    }
    return true;
}
