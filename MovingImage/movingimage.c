/*Move the image*/

#include <stdio.h>
#include <stdlib.h>

#define WID 1280
#define HEI 720
#define BAN 3

int readimage(char filename[], unsigned char *img);
int movecoordinate(unsigned char *img, unsigned char *dst, int tx, int ty);

int main()
{
    FILE *fp;
    unsigned char *img, *dst;
    char filename[100];
    char makefile[100];
    const int tx = -46;
    const int ty = -6;

    sprintf(filename, "./source/01/left.ppm");
    if((img = calloc(WID * HEI * BAN, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }

    readimage(filename, img);

    if((dst = calloc(WID * HEI * BAN, sizeof(unsigned char))) == NULL)
    {
        printf("Not Use Memory\n");
        return EXIT_FAILURE;
    }

    movecoordinate(img, dst, tx, ty);

    sprintf(makefile, "./result/01/left_fixed.ppm");

    if((fp = fopen(makefile, "wb")) == NULL)
    {
        printf("Not Make %s\n", makefile);
        return EXIT_FAILURE;
    }

    fprintf(fp, "P6\n%d %d\n255\n", WID, HEI);
    fwrite(dst, sizeof(unsigned char), WID * HEI * BAN, fp);
    fclose(fp);

    free(img);
    free(dst);

    return 0;
}

int readimage(char filename[], unsigned char *img)
{
    FILE *fp;
    
    if((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        return EXIT_FAILURE;
    }

    fscanf(fp, "P6\n1280 720\n255\n");
    fread(img, sizeof(unsigned char), WID * HEI * BAN, fp);
    fclose(fp);
}

int movecoordinate(unsigned char *img, unsigned char *dst, int tx, int ty)
{
   int i, j, k;
   int x, y;
   unsigned char *pa, *pb, *pc;

   for(i = 0, pa = dst; i < HEI; i++, pa += WID * BAN)
   {
       for(j = 0, pb = pa; j < WID; j++, pb += BAN)
       {
            x = j - tx;
            y = i - ty;

            for(k = 0, pc = pb; k < BAN; k++, pc++)
            {
                if(x >= 0 && x <= WID - 1 && y >= 0 && y <= HEI - 1)
                {
                    *pc = *(img +(y * WID * BAN) + (x * BAN) + k);
                    //printf("(%d, %d) = %d\n", x, y, *pc);
                }
                else
                {
                    *pc = 0;
                }
            }
       }
   }
}
