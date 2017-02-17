// カラー合成画像の作成
#include "composite.h"

void composite(unsigned char *img1, unsigned char *img2, int width, int height, unsigned char *dst)
{
    unsigned char *pa, *pb, *pc, *pd, *da, *db;
    int band = 3;
    int i, j;

    for (i = 0, pa = img1, pc = img2, da = dst; i < height; i++, pa += width, pc += width, da += width * band)
    {
        for (j = 0, pb = pa, pd = pc, db = da; j < width; j++, pb++, pd++, db += band)
        {
            *db = *pb;
            *(db + 1) = *pd;
            *(db + 2) = *pd;
        }
    }
}
