// 画像用にメモリを動的に確保する
#include <stdio.h>
#include <stdlib.h>
#include "imemory.h"

unsigned char *memoryppm(int width, int height)
{
    unsigned char *img;
    int band = 3;

    if ((img = calloc(width * height * band, sizeof(unsigned char))) == NULL)
    {
        printf("メモリが確保できません\n");
        exit(1);
    }
    return img;
}

unsigned char *memorypgm(int width, int height)
{
    unsigned char *img;

    if ((img = calloc(width * height, sizeof(unsigned char))) == NULL)
    {
        printf("メモリが確保できません\n");
        exit(1);
    }
    return img;
}
