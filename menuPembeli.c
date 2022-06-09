#include <stdio.h>
#include "others.h"

void searchItem(){
    clear();
    int input;
    titlePembeli();
    printf("| Kategori Barang :                              |\n");
    printf("| 1. Laptop                                      |\n");
    printf("| 2. Lisensi Software                            |\n");
    printf("| 3. Aksesoris                                   |\n");
    printf("+================================================+\n");
    printf("Pilih [1 - 3] : "); scanf("%d", &input);
    if(input == 1){
        
    }
    else if(input == 2){

    }
    else if(input == 3){

    }
    else{
        printf("Pilih salah!\n");
    }
}

void transaksi(){
    clear();
}   

void review(){
    //review barang
}

void menuPembeli(){
    int input;
    clear();
    titlePembeli();
    printf("| 1. Mencari Nama Barang                         |\n");
    printf("| 2. Transaksi Pembelian Barang                  |\n");
    printf("| 3. Melihat Review Toko                         |\n");
    printf("| 4. Kembali                                     |\n");
    printf("+================================================+\n");
    printf("Pilih [1 - 4] : "); scanf("%d", &input);
    enum option{SEARCH = 1, TRANSACTION, REVIEW, BACK};
    switch(input){
        case SEARCH:
            searchItem();
            system("pause");
            break;
        case TRANSACTION:
            transaksi();
            system("pause");
            break;
        case REVIEW:
            review();
            system("pause");
            break;
        case BACK:
            break;
        default:
            printf("Pilih salah!\n");
            system("pause");
            break;
    }
    if(input != BACK) menuPembeli();
}