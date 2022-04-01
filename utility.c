#include <stdio.h>
#include <stdbool.h>
#include "others.h"

void clear(){
    #ifdef _WIN32
        std : system("cls");
    #else
        std : system("clear");
    #endif
}

void pause(){
    char pil;
    bool loop = true;
    do{
        printf("\n\nApakah anda ingin melanjutkan program?(y/t)\nPilihan: ");
        scanf("%c", &pil); getchar();
        if(pil == 'y' || pil == 'Y'){
            loop = false;
            break;
        }
        else if(pil == 't' || pil == 'T'){
            loop = false;
            exit(0);
        }
    } while(loop);
}