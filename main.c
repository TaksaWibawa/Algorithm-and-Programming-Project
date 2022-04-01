#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "others.h"

int main(){
    int pil;
    enum option{BUYER = 1, SELLER, EXIT};
    do{
        clear();
        titleUtama();
        printf("| 1. Masuk Sebagai Pembeli                       |\n");
        printf("| 2. Masuk Sebagai Penjual                       |\n");
        printf("| 3. Keluar                                      |\n");
        printf("+================================================+\n");
        printf("Pilih [1 - 3] : "); scanf("%d", &pil);
        switch(pil){
            case BUYER:
                menuPembeli();
                pause();
                break;
            case SELLER:
                menuPenjual();
                pause();
                break;
            case EXIT:
                titleUtama();
                printf("Terima kasih telah menggunakan program kami!\n");
                exit(0);
                break;
            default:
                printf("Pilihan Salah!\n");
                break;
        }
    } while(pil != EXIT);
}