#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "others.h"

typedef struct login {
    char user[20];
    char pass[20];
} login;

void addUser(){
    login info;
    FILE* log;
    log = fopen("database/log.bin", "ab");
    printf("\nTambah Data\n"); fflush(stdin);
    printf("Masukkan Username: "); scanf("%[^\n]s", info.user); fflush(stdin);
    printf("Masukkan Password: "); scanf("%[^\n]s", info.pass); fflush(stdin);
    fwrite(&info, sizeof(login), 1, log);
    fclose(log);
}

void displayUser(){
    login info;
    int i = 1;
    FILE* log;
    log = fopen("database/log.bin", "rb");
    while(fread(&info, sizeof(login), 1, log)){
        printf("\nNo       : %d\n", i);
        printf("Username : %s\n", info.user);
        printf("Password : %s\n", info.pass);
        i++;
    }
    fclose(log);
}

void deleteUser(){
    displayUser();
    login info;
    FILE* log;
    FILE* temp;
    int found = 0;
    char username[20];
    log = fopen("database/log.bin", "rb");
    temp = fopen("database/temp.bin", "wb");
    fflush(stdin);
    printf("\nMasukkan username: "); scanf("%[^\n]s", username);
    while(fread(&info, sizeof(login), 1, log)){
        if(strcmp(info.user, username) == 0){
            found = 1;
        } else fwrite(&info, sizeof(login), 1, temp);
    }
    fclose(log);
    fclose(temp);

    if(found){
        printf("\nData berhasil dihapus\n");
        temp = fopen("database/temp.bin", "rb");
        log = fopen("database/log.bin", "wb");

        while(fread(&info, sizeof(login), 1, temp)){
            fwrite(&info, sizeof(login), 1, log);
        } 
        fclose(log);
        fclose(temp);

    } else printf("\nData tidak ditemukan!\n");
    printf("\nData setelah penghapusan: \n");
    displayUser();
}

int userMenu(){
    int pil;
    enum option{CREATE = 1, READ, DELETE, EXIT};
    do{
        clear();
        titleDataUser();
        printf("| 1. Menambahkan Admin Penjual                   |\n");
        printf("| 2. Menampilkan Data Admin                      |\n");
        printf("| 3. Menghapus Data Admin                        |\n");
        printf("| 4. Kembali                                     |\n");
        printf("+================================================+\n");
        printf("Pilih [1-4] : "); scanf("%d", &pil);
        switch(pil){
            case CREATE:
                addUser();
                pause();
                break;
            case READ:
                displayUser();
                pause();
                break;
            case DELETE:
                deleteUser();
                pause();
                break;
            case EXIT:
                break;
            default:
                break;
        }
    }while(pil != EXIT);
}