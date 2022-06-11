#include <stdio.h>
#include <conio.h>

void clear(){
    #ifdef _WIN32
        std : system("cls");
    #else
        std : system("clear");
    #endif
}

void pause(){
    printf("Press any key to continue...");
    getch();
}