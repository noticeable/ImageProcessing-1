#include <stdio.h>
#include <stdlib.h>
#include "imemory.h"
#include "readimage.h"

int main()
{
    FILE *fp;
    unsigned char *img1, *img2;
    char filename[100];
    const int width = 1280;
    const int height = 720;
    const int band = 3;

    /*if ((img1 = calloc(width * height * band, sizeof(unsigned char))) == NULL)
    {
        printf("メモリが確保できません\n");
        exit(1);
    }
    */
    img1 = memoryppm(width, height);
    sprintf(filename, "148.ppm");
    readppm(filename, img1);

    printf("終了");
    return 0;
}
