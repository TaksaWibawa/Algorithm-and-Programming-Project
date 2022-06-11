#include <stdio.h>
#include "menu.h"
#include "others.h"

typedef struct Item {
    int kodeBarang;
    int jumlah;
    char nama[20];
    long harga;
} Item;

void listItem(){
    clear();
    Item d1;
    FILE* dataBarang;
    dataBarang = fopen("database/dataBarang.bin", "rb");
    int i = 1;
    titlePembeli();
    printf("%-4s %-14s %-20s %-15s %-15s\n", "No", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Item), 1, dataBarang)){
        printf("%-4d %-14d %-20s %-15ld %-15d\n", i, d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
        i++;
    }
    fclose(dataBarang);
}

void transaction(){
    clear();
    menuCashier();
}


void menuPembeli(){
    int input;
    enum option{SEARCH = 1, TRANSACTION, BACK};
    do{
        clear();
        titlePembeli();
        printf("| 1. Melihat List Barang                         |\n");
        printf("| 2. Transaksi Pembelian Barang                  |\n");
        printf("| 3. Kembali                                     |\n");
        printf("+================================================+\n");
        printf("Pilih [1 - 3] : "); scanf("%d", &input);
        switch(input){
            case SEARCH:
                listItem();
                pause();
                break;
            case TRANSACTION:
                transaction();
                pause();
                break;
            case BACK:
                break;
            default:
                break;
        }
    }while(input != BACK);
}