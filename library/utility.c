#include <stdio.h>
#include "others.h"

void clear(){
    #ifdef _WIN32
        std : system("cls");
    #else
        std : system("clear");
    #endif
}