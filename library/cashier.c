#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "others.h"

typedef struct Barang {
    int kodeBarang;
    int jumlah;
    char nama[20];
    long harga;
} Barang;

typedef struct dataLogin {
    char user[20];
    char pass[20];
} dataLogin;

void initialize(){
    FILE* item;
    item = fopen("database/item.bin", "wb");
    fclose(item);
}

char username[20];
char password[20];

int logInfo(){
    clear();
    FILE* log;
    dataLogin info;
    int masuk;
    log = fopen("database/log.bin", "rb");
    titleKasir();
    fflush(stdin);
    printf("Username: "); scanf("%[^\n]s", username); fflush(stdin);
    printf("Password: "); scanf("%[^\n]s", password); fflush(stdin);

    while(fread(&info, sizeof(dataLogin), 1, log)){
        if((strcmp(username, info.user) == 0) && (strcmp(password, info.pass) == 0)){
            masuk = 1;
            break;
        } else {
            masuk = 2;
        }
    }
    fclose(log);
    return masuk;
}

int dataSize(){
    FILE *data;
    data = fopen("database/dataBarang.bin", "rb");
    fseek(data, 0, SEEK_END);
    int jml = ftell(data) / sizeof(Barang);
    fclose(data);
    return jml;
}

int itemSize(){
    FILE *item;
    item = fopen("database/item.bin", "rb");
    fseek(item, 0, SEEK_END);
    int jml = ftell(item) / sizeof(Barang);
    fclose(item);
    return jml;
}

void itemList(){
    Barang d1;
    FILE* data;
    data = fopen("database/dataBarang.bin", "rb");
    
    int i = 1;
    
    printf("\n%-4s %-14s %-20s %-15s %-15s\n", "No", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Barang), 1, data)){
        printf("%-4d %-14d %-20s %-15ld %-15d\n", i, d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
        i++;
    }
    fclose(data);
}

void displayStock(){
    Barang d1;
    FILE* item;
    item = fopen("database/dataBarang.bin", "rb");
    
    int i = 1;
    
    printf("\n%-4s %-14s %-20s %-15s %-15s\n", "No", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Barang), 1, item)){
        printf("%-4d %-14d %-20s %-15ld %-15d\n", i, d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
        i++;
    }
    fclose(item);
}

void displayItem(){
    Barang d1;
    FILE* item;
    item = fopen("database/item.bin", "rb");
    
    int i = 1;
    
    printf("\n%-4s %-14s %-20s %-15s %-15s\n", "No", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&d1, sizeof(Barang), 1, item)){
        printf("%-4d %-14d %-20s %-15ld %-15d\n", i, d1.kodeBarang, d1.nama, d1.harga, d1.jumlah);
        i++;
    }
    fclose(item);
}

void addItem(){
    Barang d1;
    Barang dataBeli;

    FILE* data;
    FILE* item;

    data = fopen("database/dataBarang.bin", "rb");
    item = fopen("database/item.bin", "ab");
    itemList();
    int kode, found;
    long total;
    int jmlItem;

    printf("Masukkan pilihan (kode barang) : "); scanf("%d", &kode);
    while(fread(&d1, sizeof(Barang), 1, data)){
        if(d1.kodeBarang == kode){
            found = 1;
            if(d1.jumlah != 0){
                printf("\nNama barang   : %s", d1.nama);
                printf("\nJumlah barang : "); scanf("%d", &jmlItem);
                total = (d1.harga * jmlItem);
                printf("Harga barang  : %ld", total);

                strcpy(dataBeli.nama, d1.nama);
                dataBeli.jumlah = jmlItem;
                dataBeli.harga = total;
                dataBeli.kodeBarang = d1.kodeBarang;
                
                fwrite(&dataBeli, sizeof(Barang), 1, item);
            } else {
                printf("\nMaaf, Stok Habis\n");
            }
        }
    }
    fclose(data);
    fclose(item);
    if(!found) printf("\nBarang Tidak Ada!\n");
}

void changeItem(){
    Barang dataBeli;
    Barang d1;

    FILE* item;
    FILE* temp;
    FILE* data;

    item = fopen("database/item.bin", "rb");
    temp = fopen("database/temp.bin", "wb");
    data = fopen("database/dataBarang.bin", "rb");

    displayItem();

    int kode, found = 0;
    printf("\nMasukkan kode barang: "); scanf("%d", &kode);

    printf("Data yang akan diubah: \n");
    printf("%-14s %-20s %-15s %-15s\n", "Kode Barang", "Nama Barang", "Harga", "Jumlah");
    while(fread(&dataBeli, sizeof(Barang), 1, item)){
        if(dataBeli.kodeBarang == kode){
            
            while(fread(&d1, sizeof(Barang), 1, data)){
                if(d1.kodeBarang == dataBeli.kodeBarang){
                    found = 1;
                    printf("%-14d %-20s %-15ld %-15d\n", dataBeli.kodeBarang, dataBeli.nama, dataBeli.harga, dataBeli.jumlah);
                    
                    printf("Jumlah barang : "); scanf("%d", &dataBeli.jumlah);
                    dataBeli.harga = (d1.harga * dataBeli.jumlah);
                }
            }
            fwrite(&dataBeli, sizeof(Barang), 1, temp);
        } else {
            fwrite(&dataBeli, sizeof(Barang), 1, temp);
        }
    }
    fclose(item);
    fclose(data);
    fclose(temp);

    if(found){
        temp = fopen("database/temp.bin", "rb");
        item = fopen("database/item.bin", "wb");

        while(fread(&dataBeli, sizeof(Barang), 1, temp)){
            fwrite(&dataBeli, sizeof(Barang), 1, item);
        }
        fclose(item);
        fclose(temp);
        displayItem();
    } else printf("Data tidak ditemukan!\n");
}

void deleteItem(){
    displayItem();
    Barang d1;
    FILE* item;
    FILE* temp;
    item = fopen("database/item.bin", "rb");
    temp = fopen("database/temp.bin", "wb");
    int kode, found = 0;
    printf("Masukkan kode barang: "); scanf("%d", &kode);

    while(fread(&d1, sizeof(Barang), 1, item)){
        if(d1.kodeBarang == kode){
            found = 1;
        } else fwrite(&d1, sizeof(Barang), 1, temp);
    }
    fclose(item);
    fclose(temp);

    if(found){
        temp = fopen("database/temp.bin", "rb");
        item = fopen("database/item.bin", "wb");

        while(fread(&d1, sizeof(Barang), 1, temp)){
            fwrite(&d1, sizeof(Barang), 1, item);
        } 
        fclose(item);
        fclose(temp);

    } else printf("Barang tidak ditemukan!\n");

    printf("\nItem setelah penghapusan: \n");
    displayItem();
}

void decrementStock(){
    Barang d1;
    Barang t1;
    int found;

    FILE* item;
    FILE* data;
    FILE* temp;

    item = fopen("database/item.bin", "rb");
    data = fopen("database/dataBarang.bin", "rb");
    temp = fopen("database/temp.bin", "wb");

    while(fread(&t1, sizeof(Barang), 1, item)){
        while(fread(&d1, sizeof(Barang), 1, data)){
            if(d1.kodeBarang == t1.kodeBarang){
                found = 1;
                d1.jumlah -= t1.jumlah;
            }
            fwrite(&d1, sizeof(Barang), 1, temp);
        }
    }
    fclose(item);
    fclose(data);
    fclose(temp);

    if(found){
        temp = fopen("database/temp.bin", "rb");
        data = fopen("database/dataBarang.bin", "wb");

        while(fread(&d1, sizeof(Barang), 1, temp)){
            fwrite(&d1, sizeof(Barang), 1, data);
        } 
        fclose(data);
        fclose(temp);
    }
}

void checkoutItem(){
    Barang d1;
    long total = 0;
    long tunai = 0;
    long kembalian;
    int i = 0;

    int jmlBarang = itemSize();

    char nama[jmlBarang][20];
    int jml[jmlBarang];
    long harga[jmlBarang];

    FILE* item;
    FILE* strukBelanja;

    item = fopen("database/item.bin", "rb");
    strukBelanja = fopen("strukBelanja.txt", "w");

    printf("\n==================================================================\n");
    printf("%-3s %-28s %-7s %-15s\n", "No", "Barang", "Qty", "Sub Total");

    while(fread(&d1, sizeof(Barang), 1, item)){
        printf("%-3d %-28s %-7d %-15ld\n", i + 1,  d1.nama, d1.jumlah, d1.harga);
        
        strcpy(nama[i], d1.nama);
        jml[i] = d1.jumlah;
        harga[i] = d1.harga;

        total += d1.harga;
        i++;
    }

    printf("\n==================================================================\n");
    printf("Total Belanja  : %ld\n", total);

    while(tunai < total){
        printf("Tunai          : "); scanf("%ld", &tunai);
    }

    kembalian = tunai - total;
    printf("Kembalian      : %ld", kembalian);



    time_t waktu_skrg;
    time(&waktu_skrg);

    fprintf(strukBelanja, "====================================================\n");
    fprintf(strukBelanja, "=                    Mayun Comp                    =\n");
    fprintf(strukBelanja, "====================================================\n");

    fprintf(strukBelanja, "            Dalung Permai blok X no. 666            \n");
    fprintf(strukBelanja, "                  www.mayuncomp.com                 \n");
    fprintf(strukBelanja, "====================================================\n\n");

    fprintf(strukBelanja, "Date       : %s\n", ctime(&waktu_skrg));
    fprintf(strukBelanja, "User\t: %s\n\n", username);
    fprintf(strukBelanja, "\n====================================================\n");
    fprintf(strukBelanja, "%-3s %-28s %-7s %-15s\n", "No", "Barang", "Qty", "Sub Total");

    for(i = 0; i < jmlBarang; i++){
        fprintf(strukBelanja, "%-3d %-28s %-7d %-15ld\n", i + 1,  nama[i], jml[i], harga[i]);
    }
    fprintf(strukBelanja, "\n====================================================\n");
    fprintf(strukBelanja, "Total Belanja  : Rp. %ld\n", total);
    fprintf(strukBelanja, "Tunai          : Rp. %ld\n", tunai);
    fprintf(strukBelanja, "Kembalian      : Rp. %ld\n", kembalian);
    fprintf(strukBelanja, "\n====================================================\n");

    fprintf(strukBelanja, "                      Thank You                     \n");
    fprintf(strukBelanja, "                  Please Come Again                 \n");
    fprintf(strukBelanja, "                Telp  : 081234567890                \n");
    fprintf(strukBelanja, "            E-mail : mayuncomp@gmail.com            \n");
    fprintf(strukBelanja, "====================================================\n\n");

    // tutup file
    fclose(strukBelanja);
    fclose(item);

    //membuka file laba pada macOS
    // system("open /Users/devakrishna/Documents/Deva/Smt II/Tugas/10. Praktikum Alpro/FINAL PROJECT/strukBelanja.txt");
    system("START /MIN NOTEPAD /P strukBelanja.txt");
    decrementStock();
    remove("database/item.bin");
}

int menuCashier(){
    int input;
    int log = logInfo();
    char retry;
    do{
        if(log == 1){
            clear();
            titleKasir();
            printf("Barang Saat Ini:\n");
            displayItem();
            printf("\n=================================\n\n");
            printf("1. Masukkan Barang ke Keranjang\n");
            printf("2. Lihat Barang dan Stok\n");
            printf("3. Ubah Barang di Keranjang\n");
            printf("4. Hapus Barang di Keranjang\n");
            printf("5. Proses Checkout\n");
            printf("6. Kembali\n");
            printf("=================================\n");
            printf("Pilih [1 - 6] : "); scanf("%d", &input);
            switch(input){
                case 1:
                    addItem();
                    pause();
                    break;
                case 2:
                    displayStock();
                    pause();
                    break;
                case 3:
                    changeItem();
                    pause();
                    break;
                case 4:
                    deleteItem();
                    pause();
                    break;
                case 5:
                    checkoutItem();
                    pause();
                    break;
                case 6:
                    break;
                default:
                    break;
            }
        }
        else if(log == 2){
            do{
                printf("\n Password salah!"); fflush(stdin);
                printf("\ncoba lagi? <y/n> ? : "); scanf("%c", &retry);
                if ((retry == 'y') || (retry == 'Y')){
                    menuCashier();
                    break;
                }
                else if ((retry == 'n') || (retry == 'N')){
                    main();
                    break;
                }
            }while(retry != 'y' || retry != 'Y' || retry != 'n' || retry != 'N');
        }
    }while(input != 6);
}

//waktu decrement stok, hanya barang pertama yang masuk ke list yang berkurang, dan ketika mencapai 0,
//barang masih ada
