#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Item {
    int pk;
    int jumlah;
    char nama[20];
    long harga;
} Item;

FILE *data;

int menu(){
    int input;
    system("clear");
    printf("\nProgram Database Toko Mayun\n");
    printf("=================================\n");
    printf("1. Tambah Barang\n");
    printf("2. Tampilkan Barang\n");
    printf("3. Ubah Data Barang\n");
    printf("4. Hapus Data Barang\n");
    printf("5. Keluar\n");
    printf("=================================\n");
    printf("Pilih [1 - 5] : "); scanf("%d", &input);
    return input;
}

void checkData(){
    system("clear");
    

    if ((data = fopen("data.bin","rb")) == NULL){
        printf("Error: File tidak ada, akan dibuatkan data baru\n");
        data = fopen("data.bin", "wb");
    } else {
        printf("Data ditemukan!\n");
    }
    fclose(data);
    printf("Press any key to continue");
    system("read -n1 -p '' key");
}

int dataSize(){
    int ukuran;
    ukuran = sizeof(data);
    return ukuran / sizeof(Item);
}

void addData(){

}

int main(){
    checkData();
    FILE *data = fopen("data.bin", "ab");
    dataSize();

    int pil = menu();
    char lanjut;

    enum option{CREATE = 1, READ, UPDATE, DELETE, FINISH};

    while(pil != FINISH){
        switch (pil){
            case CREATE:
                printf("----Menambah Data Barang----\n\n");
                int bab = sizeof(Item);
                printf("%d", bab);
                addData();
                break;
            
            case READ:
                printf("");
        }
    }

}