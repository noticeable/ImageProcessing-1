#ifndef WABUN_H
#define WABUN_H
// 画像データを返す

//void wabun1x3(unsigned char *, unsigned char *, unsigned char *,int, int);

void wabun1x3(unsigned char *img1, unsigned char *img2, unsigned char *dst,int width, int height)
{
    unsigned char *pa, *pb, *pc, *pd, *pe, *pf, *da, *db;
    int mask = 3;
    double left, right, suml, sumr, buns, wabun;
    double alpha = 0.1; // 分母に加える定数
    int i, j, k;

    // 類似度の計算
    for (i = 0, pa = img1, pd = img2, da = dst; i < height; i++, pa += width, pd += width, da += width)
    {
        for (j = 0, pb = pa, pe = pd, db = da; j < width; j++, pb++, pe++, db++)
	{
            suml = 0;
            sumr = 0;
            if (j != 0 || j != width - 1)
            {
                for (k = 0, pc = pb - 1, pf = pe - 1; k < mask; k++, pc++, pf++)
                {
                    left = (double)*pc; // １枚目を代入
                    right = (double)*pf; // ２枚目を代入
                    if (k == 0)
                    {
                        suml += left;
                        sumr += right;
                    }
                    if (k == 1)
                    {
                        suml += left;
                        sumr += right;
                    }
                    else
                    {
                        suml += left;
                        sumr += right;   
                    }
                }
                buns = fabs(suml - sumr); // 分子を計算
                wabun = (buns / (suml + sumr + alpha)) * 2040;
                if (wabun > 255)
                {
                    *db = 0;   
                }
                else
                {
                    *db = (unsigned char)(255 - wabun);
                }
            }
            else
            {
                *db = 0;
            }
        }
    }
}


void wabun2x2(unsigned char *img1, unsigned char *img2, unsigned char *dst,int width, int height)
{
    unsigned char *pa, *pb, *pc, *pd, *pe, *pf, *pg, *ph, *da, *db;
    int mask = 2;
    double left, right, suml, sumr, buns, wabun;
    double alpha = 0.1; // 分母に加える定数
    int i, j, k, l;

    // 類似度の計算
    for (i = 0, pa = img1, pe = img2, da = dst; i < height; i++, pa += width, pe += width, da += width)
    {
        for (j = 0, pb = pa, pf = pe, db = da; j < width; j++, pb++, pf++, db++)
	{
            suml = 0;
            sumr = 0;
            if (i < height - 1 && j < width - 1)
            {
                // マスク処理 
                for (k = 0, pc = pb, pg = pf; k < mask; k++, pc += width, pg += width)
                {
                    for (l = 0, pd = pc, ph = pg; l < mask; l++, pd++, ph++)
                    {
                        left = (double)*pd; // １枚目を代入
                        right = (double)*ph; // ２枚目を代入
                        if (k == 0)
                        {
                            suml += left;
                            sumr += right;
                        }
                        if (k == 1)
                        {
                            suml += left;
                            sumr += right;
                        }
                        else
                        {
                            suml += left;
                            sumr += right;   
                        }
                    }
                }
                buns = fabs(suml - sumr); // 分子を計算
                wabun = (buns / (suml + sumr + alpha)) * 2040;
                if (wabun > 255)
                {
                    *db = 0;   
                }
                else
                {
                    *db = (unsigned char)(255 - wabun);
                }
            }
            else
            {
                *db = 0;
            }
        }
    }
}

#endif
