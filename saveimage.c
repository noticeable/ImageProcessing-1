// 画像データを保存する(ppm, pgm)
#include <stdio.h>
#include <stdlib.h>
#include "saveimage.h"

void saveppm(char filename[], unsigned char *img, int width, int height)
{
    FILE *fp;
    int band = 3;

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }

    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    fwrite(img, sizeof(unsigned char), width * height * band, fp);

    fclose(fp);   
}

void savepgm(char filename[], unsigned char *img, int width, int height)
{
    FILE *fp;

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }

    fprintf(fp, "P5\n%d %d\n255\n", width, height);
    fwrite(img, sizeof(unsigned char), width * height, fp);
 
    fclose(fp);   
}
