/*画像を角度θだけ回転させる*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readppm.h"

#define WID 1280
#define HEI 720
#define BAN 3
#define PI 3.141592

void helmert(unsigned char *img, unsigned char *dst, double deg);

int main()
{
    FILE *fp;
    unsigned char *img, *dst;
    char filename[256];
    char makefile[256];
    const double deg = -0.0011;

    sprintf(filename, "./source/02/left_fixed.ppm");

    if((img = calloc(WID * HEI * BAN, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }
    
    readppm(filename, img); // ppm画像の読み込み

    if((dst = calloc(WID * HEI * BAN, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }

    helmert(img, dst, deg);
    
    sprintf(makefile, "./result/02/left_rotated.ppm");
    
    if((fp = fopen(makefile, "wb")) == NULL)
    {
        printf("Not Make %s\n", makefile);
        return EXIT_FAILURE;
    }

    fprintf(fp, "P6\n%d %d\n255\n", WID, HEI);
    fwrite(dst, sizeof(unsigned char), WID * HEI * BAN, fp);
    fclose(fp);

    return 0;
}

void helmert(unsigned char *img, unsigned char *dst, double deg)
{
    unsigned char *pa, *pb, *pc;
    double u, v, ux, vy, num;
    double rad = deg * PI / 180.0;
    int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    int i, j, k;
    
    for(i = 0, pa = dst; i < HEI; i++, pa += WID * BAN)
    {
        for(j = 0, pb = pa; j < WID; j++, pb += BAN)
        {
            u = j * cos(rad) - (i * sin(rad));
            v = j * sin(rad) + (i * cos(rad));

            // Bi-linear法
            if(u > 0 && u < WID -1 && v > 0 && v < HEI - 1)
            {
                Ax = (int)floor(u);
                Ay = (int)floor(v);
                Bx = (int)floor(u + 1);
                By = (int)floor(v);
                Cx = (int)floor(u + 1);
                Cy = (int)floor(v + 1);
                Dx = (int)floor(u);
                Dy = (int)floor(v + 1);
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else if(u == 0 || u == WID && v == 0 || v == HEI)
            {
                Ax = (int)u;
                Ay = (int)v;
                Bx = 0;
                By = 0;
                Cx = 0;
                Cy = 0;
                Dx = 0;
                Dy = 0;
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else if(u == 0 && v > 0 && v < HEI - 1)
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = 0;
                By = 0;
                Cx = 0;
                Cy = 0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else if(u == WID - 1 && v > 0 && v < HEI - 1)
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = 0;
                By = 0;
                Cx = 0;
                Cy = 0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else if(u > 0 && u < WID - 1 && v == 0)
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);
                By = (int)v;
                Cx = 0;
                Cy = 0;
                Dx = 0;
                Dy = 0;
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else if(u > 0 && u < WID - 1 && v == HEI - 1)
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);
                By = (int)v;
                Cx = 0;
                Cy = 0;
                Dx = 0;
                Dy = 0;
                ux = modf(u, &num);
                vy = modf(v, &num);
            }
            else
            {
                Ax = (int)floor(u);
                Ay = (int)floor(v);
                Bx = (int)floor(u + 1);
                By = (int)floor(v);
                Cx = (int)floor(u + 1);
                Cy = (int)floor(v + 1);
                Dx = (int)floor(u);
                Dy = (int)floor(v + 1);
                ux = modf(u, &num);
                vy = modf(v, &num);
            }

            for(k = 0, pc = pb; k < BAN; k++, pc++)
            {
                if(u >= 0 && u <= WID - 1 && v >= 0 && v <= HEI - 1)
                {
                    *pc = (unsigned char)((img[(Ay * WID * BAN) + (Ax * BAN) + k] * (1 - ux) * (1 - vy)) + (img[(By * WID * BAN) + (Bx * BAN) + k] * ux * (1 - vy)) + (img[(Dy * WID * BAN) + (Dx * BAN) + k] * (1 - ux) * vy) + (img[(Cy * WID * BAN) + (Cx * BAN) + k] * ux * vy));
                }
                else
                {
                    *pc = 0;
                }
            }
        }
    }
}
