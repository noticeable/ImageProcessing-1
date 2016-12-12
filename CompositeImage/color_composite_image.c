/*Generate a color composite image*/

#include <stdio.h>
#include <stdlib.h>
#include "readppm.h"

#define WID 1280
#define HEI 720

// generate the color composite image
void generate_ccimage(char filename[], unsigned char *img1, unsigned char *img2);

int main()
{
    unsigned char *img1, *img2;
    char filename_1[256];
    char filename_2[256];
    char makefile[256];
    
    sprintf(filename_1, "./source/01/left_fixed.ppm");
    sprintf(filename_2, "./source/01/center.ppm");
    sprintf(makefile, "./result/01/composite_cl.ppm");

    if((img1 = calloc(WID * HEI * 3, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }

    if((img2 = calloc(WID * HEI * 3, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }

    readppm(filename_1, img1);
    readppm(filename_2, img2);

    generate_ccimage(makefile, img1, img2);

    free(img1);
    free(img2);

    return 0;
}

void generate_ccimage(char filename[], unsigned char *img1, unsigned char *img2)
{
    FILE *fp;
    unsigned char *dst, *pa, *pb, *pc, *pd, *da, *db;
    int i, j;
    double r1, r2, g1, g2, b1, b2;
    
    if((dst = calloc(WID * HEI * BAN, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        exit(1);
    }

    for(i = 0, pa = img1, pc = img2, da = dst; i < HEI; i++, pa += WID * BAN, pc += WID * BAN, da += WID * BAN)
    {
        for(j = 0, pb = pa, pd = pc, db = da; j < WID; j++, pb += BAN, pd += BAN, db += BAN)
        {
            r1 = (double)*pb;
            g1 = (double)*(pb + 1);
            b1 = (double)*(pb + 2);
            r2 = (double)*pd;
            g2 = (double)*(pd + 1);
            b2 = (double)*(pd + 2);

            *db = (unsigned char)((r1 * 0.298912) + (g1 * 0.586611) + (b1 * 0.114478));
            *(db + 1) = (unsigned char)((r2 * 0.298912) + (g2 * 0.586611) + (b2 * 0.114478));
            *(db + 2) = *(db + 1);
        }
    }

    if((fp = fopen(filename, "wb")) == NULL)
    {
        printf("Not Make Image File\n");
        exit(1);
    }

    fprintf(fp, "P6\n%d %d\n255\n", WID, HEI);
    fwrite(dst, sizeof(unsigned char), WID * HEI * BAN, fp);
    fclose(fp);
    free(dst);
}
