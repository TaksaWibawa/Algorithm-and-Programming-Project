#include <stdio.h>
#include "login.h"

typedef struct Item {
    int kodeBarang;
    int jumlah;
    char nama[20];
    long harga;
} Item;

void displayData(){
    Item d1;
    FILE* dataBarang;
    dataBarang = fopen("database/dataBarang.bin", "rb");
    int i = 1;
    titlePenjual();
    printf("%-4s %-14s %-20s %-15s %-15s\n", "No", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Item), 1, dataBarang)){
        printf("%-4d %-14d %-20s %-15ld %-15d\n", i, d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
        i++;
    }
    fclose(dataBarang);
}

void addData(){ 
    clear();
    int i, jumlah;
    Item *s;
    FILE* dataBarang;
    dataBarang = fopen("database/dataBarang.bin", "ab");
    s = (Item*) calloc(jumlah, sizeof(Item));

    titlePenjual();
    printf(" Jumlah Barang yang Akan Didata : "); scanf("%d", &jumlah);
    printf("\n");
    for(i = 0; i < jumlah; i++){
        printf(" Kode Barang   : "); scanf("%d", &s[i].kodeBarang); fflush(stdin);
        printf(" Nama Barang   : "); scanf("%s", s[i].nama); fflush(stdin);
        printf(" Harga Barang  : "); scanf("%ld", &s[i].harga); fflush(stdin);
        printf(" Jumlah Barang : "); scanf("%d", &s[i].jumlah); fflush(stdin);
        printf("\n");
        fwrite(&s[i], sizeof(Item), 1, dataBarang);
    }
    printf(" Data Barang Berhasil Ditambahkan!\n");
    printf("+================================================+\n");
    fclose(dataBarang);
}

void deleteData(){
    displayData();
    Item d1;
    FILE* dataBarang;
    FILE* temp;
    dataBarang = fopen("database/dataBarang.bin", "rb");
    temp = fopen("database/temp.bin", "wb");
    int kode, found = 0;
    printf("Masukkan kode barang: "); scanf("%d", &kode);

    while(fread(&d1, sizeof(Item), 1, dataBarang)){
        if(d1.kodeBarang == kode){
            found = 1;
        } else fwrite(&d1, sizeof(Item), 1, temp);
    }
    fclose(dataBarang);
    fclose(temp);

    if(found){
        temp = fopen("database/temp.bin", "rb");
        dataBarang = fopen("database/dataBarang.bin", "wb");

        while(fread(&d1, sizeof(Item), 1, temp)){
            fwrite(&d1, sizeof(Item), 1, dataBarang);
        } 
        fclose(dataBarang);
        fclose(temp);

    } else printf("Data tidak ditemukan!\n");

    printf("\nData setelah penghapusan: \n");
    displayData();
}

void updateData(){
    displayData();
    Item d1;
    FILE* dataBarang;
    FILE* temp;
    dataBarang = fopen("database/dataBarang.bin", "rb");
    temp = fopen("database/temp.bin", "wb");
    int kode, found = 0;
    printf("Masukkan kode barang: "); scanf("%d", &kode);

    printf("Data yang akan diubah: \n");
    printf("%-14s %-20s %-15s %-15s\n", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Item), 1, dataBarang)){
        if(d1.kodeBarang == kode){
            found = 1;
            printf("%-14d %-20s %-15ld %-15d\n", d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
            printf("Ubah Data:\n");
            fflush(stdin);
            printf("Nama barang   : "); scanf("%[^\n]s", d1.nama);
            fflush(stdin);
            printf("Harga barang  : "); scanf("%ld", &d1.harga); 
            fflush(stdin);
            printf("Jumlah barang : "); scanf("%d", &d1.jumlah);
        }
        fwrite(&d1, sizeof(Item), 1, temp);
    }
    fclose(dataBarang);
    fclose(temp);

    if(found){
        temp = fopen("database/temp.bin", "rb");
        dataBarang = fopen("database/dataBarang.bin", "wb");

        while(fread(&d1, sizeof(Item), 1, temp)){
            fwrite(&d1, sizeof(Item), 1, dataBarang);
        } 
        fclose(dataBarang);
        fclose(temp);

    } else printf("Data tidak ditemukan!\n");
}

void menuPenjual(){
    int input;
    enum option{add = 1, delete, update, show, user, back};
    do{
        clear();
        titlePenjual();
        printf("| 1. Menambah Barang                             |\n");
        printf("| 2. Menghapus Barang                            |\n");
        printf("| 3. Mengubah Stok Barang                        |\n");
        printf("| 4. Menampilkan Stok Barang                     |\n");
        printf("| 5. Data User Penjual                           |\n");
        printf("| 6. Kembali                                     |\n");
        printf("+================================================+\n");
        printf("Pilih [1 - 6] : "); scanf("%d", &input);
        switch(input){
            case add:
                addData();
                system("pause");
                break;
            case delete:
                deleteData();
                system("pause");
                break;
            case update:
                updateData();
                system("pause");
                break;
            case show:
                displayData();
                system("pause");
                break;
            case user:
                userMenu();
                break;
            case back:
                break;
            default:
                break;
        }
    }while(input != back);
}