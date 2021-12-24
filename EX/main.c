#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *file;

int main(int argc, char *argv[]) {

// 446 - клод загрузчмка
// 64 Таблица разделов
// 2 - сигнатура

//обрабатываем параметры командной строки
file = fopen(argv[1],"wb");
int image = atoi(argv[2]) * 1024;
int chapter = atoi(argv[3]);

char PUMM[447] = {0};

fread(PUMM, 1, 446, file);
fwrite(PUMM, 1, 446, file);

for (int i = 0; i < chapter; i++){
    
    if(i == 0){

        fputc(0x00, file);
        fputc(0x01, file);
        fputc(0x01, file); 
        fputc(0x00, file);
        fputc(0x00, file);
        fputc(0x01 * (image - 512) % 64, file); 
        fputc(0x01 * (image - 512) / 64, file); 
        fputc(0x01 * i, file); 

    }

    else{

        fputc(0x00, file);
        fputc(0x01 * (image - 512) % 64, file);
        fputc(0x01 * (image - 512) / 64, file);
        fputc(0x00 * i, file);
        fputc(0x00, file);
        fputc(0x01 * (image - 512) % 64, file); 
        fputc(0x01 * (image - 512) / 64, file); 
        fputc(0x01 * i, file); 

    }

}

fputc(0x55, file);
fputc(0xAA, file);

for (int i = 0; i < image; i++) fputc (0x00,file);

fcloseall();

return 0;
}