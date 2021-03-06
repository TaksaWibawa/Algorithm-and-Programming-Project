#include <stdio.h>
#include <stdlib.h>
#include "library/menu.h"
#include "library/others.h"
#include "library/login.h"

void main(){
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
                clear();
                titleUtama();
                printf("Terima kasih telah menggunakan program kami!\n");
                exit(0);
                break;
            default:
                break;
        }
    } while(pil != EXIT);
}