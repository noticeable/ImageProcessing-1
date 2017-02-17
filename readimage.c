// 画像の読み込み用ヘッダファイル
#include <stdio.h>
#include <stdlib.h>
#include "readimage.h"

void readpgm(char filename[], unsigned char *img)
{
    FILE *fp;
    const int max_buffersize = 1024;
    char buffer[max_buffersize];
    int max_color;
    int wid, hei;

    if((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }

    // Check the file type 'P5'
    fgets(buffer, max_buffersize, fp);
    if(buffer[0] != 'P' || buffer[1] != '5')
    {
        printf("Not P5!!\n");
        exit(1);
    }

    // Input of wid and hei
    wid = 0;
    hei = 0;
    while(wid == 0 || hei == 0)
    {
        fgets(buffer, max_buffersize, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d %d", &wid, &hei);
        }
    }

    // Input of max_color
    max_color = 0;
    while(max_color == 0)
    {
        fgets(buffer, max_buffersize, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d", &max_color);
        }
    }

    fread(img, sizeof(unsigned char), wid * hei, fp);
    fclose(fp);
}

void readppm(char filename[], unsigned char *img)
{
    FILE *fp;
    const int max_buffersize = 1024;
    char buffer[max_buffersize];
    int max_color;
    int wid, hei;
    int ban = 3;

    if((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }

    // Check the file type 'P6'
    fgets(buffer, max_buffersize, fp);
    if(buffer[0] != 'P' || buffer[1] != '6')
    {
        printf("Not P6!!\n");
        exit(1);
    }

    // Input of wid and hei
    wid = 0;
    hei = 0;
    while(wid == 0 || hei == 0)
    {
        fgets(buffer, max_buffersize, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d %d", &wid, &hei);
        }
    }

    // Input of max_color
    max_color = 0;
    while(max_color == 0)
    {
        fgets(buffer, max_buffersize, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d", &max_color);
        }
    }

    fread(img, sizeof(unsigned char), wid * hei * ban, fp);
    fclose(fp);
}
