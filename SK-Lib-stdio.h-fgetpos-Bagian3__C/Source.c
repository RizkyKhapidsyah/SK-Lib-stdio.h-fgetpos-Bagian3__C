#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>

/*
    Source by CPPReference (https://en.cppreference.com)
    Modified For Learn by RK
    I.D.E : VS2022
*/

int main(void) {
    // siapkan file yang menyimpan 4 nilai tipe double
    enum { SIZE = 4 };
    FILE* fp = fopen("test.bin", "wb");
    assert(fp);
    
    int rc = fwrite((double[SIZE]) { 
        1.1, 2.2, 3.3, 4.4 
    }, sizeof(double), 
            SIZE, fp);
    
    assert(rc == SIZE);
    fclose(fp);

    // demo menggunakan fsetpos untuk kembali ke awal file
    fp = fopen("test.bin", "rb");
    fpos_t pos;
    fgetpos(fp, &pos);               // simpan awal file di pos
    double d;
    rc = fread(&d, sizeof d, 1, fp); // baca ganda pertama
    assert(rc == 1);
    printf("Nilai pertama dalam file: %.1f\n", d);
    fsetpos(fp, &pos);                 // pindahkan posisi file kembali ke awal file
    rc = fread(&d, sizeof d, 1, fp);  // baca ganda pertama lagi
    assert(rc == 1);
    printf("Nilai pertama dalam file lagi: %.1f\n", d);
    fclose(fp);

    // penanganan kesalahan demo
    rc = fsetpos(stdin, &pos);
    if (rc) {
        perror("tidak bisa fsetpos stdin");
    }

    _getch();
    return 0;
}