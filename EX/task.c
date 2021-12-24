#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
FILE *fp1;
FILE *fp2;

int main(int argc, char *argv[])
{
    char mbr[447] = {0};
    const char null = '\0';
    fp1 = fopen("mbr.iso", "rb");
    fp2 = fopen(argv[1],"wb");
    fread(mbr, 1, 446, fp1);
    fwrite(mbr, 1, 446, fp2);

 
    for(int i = 0; i<atoi(argv[3]); i++){
    if (i == 0) 
    {
        fputc(0x80, fp2);
        fputc(0x01, fp2); //golova
        fputc(0x01, fp2); //sector
        fputc(0x00, fp2);
        fputc(0x06, fp2);
        fputc(0x0f, fp2);
        fputc(0x01*(atoi(argv[2])-512)%64, fp2); //end(sector)
        fputc(0x01*(atoi(argv[2])-512)/64, fp2); //end cilinder
    }     
    if (i>0)
    {
        fputc(0x00, fp2);
        fputc(0x01*i, fp2);
        fputc(0x01*(atoi(argv[2])-512)%64, fp2); //end(sector)
        fputc(0x01*(atoi(argv[2])-512)/64, fp2); //end cilinder
        fputc(0x06, fp2);
        fputc(0x0f*i, fp2);
        fputc(0x01*(atoi(argv[2])-512)%64, fp2); //end(sector)
        fputc(0x01*(atoi(argv[2])-512)/64, fp2); //end cilinder
    }

    fputc(0x00, fp2);
    fputc(0x00, fp2);
    fputc(0x00, fp2);
    fputc(0x01*(atoi(argv[2]-512)%64),fp2);
    fputc(0x00, fp2);
    fputc(0x00, fp2);
    fputc(0x00, fp2);
    fputc(0x01*(atoi(argv[2])-512),fp2);
 }
    fputc(0x55, fp2);
    fputc(0xAA, fp2);
    for (int i = 0; i < atoi(argv[2])*1024-512; i++) fputc (0x00,fp2);
    fcloseall();
    return 0;
}
