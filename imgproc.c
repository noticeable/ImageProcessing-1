#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imgproc.h"

void grayscale(unsigned char *img, unsigned char *dst, int wid, int hei)
{
    unsigned char *pa, *pb, *pc, *da, *db;
    double r, g, b, sum;
    int band = 3;
    int i, j, k;

    for (i = 0, pa = img, da = dst; i < hei; i++, pa += wid * band, da += wid)
    {
        for (j = 0, pb = pa, db = da; j < wid; j++, pb += band, db++)
        {
            sum = 0;
            for (k = 0, pc = pb; k < band; k++, pc++)
            {
                if (k == 0)
                {
                    r = (double)*pc;
                    sum += r * 0.298912;
                }
                else if (k == 1)
                {
                    g = (double)*pc;
                    sum += g * 0.586611;
                }
                else
                {
                    b = (double)*pc;
                    sum += b * 0.114478;
                }
            }
            if (sum > 255)
            {
                *db = 255;
            }
            else
            {
                *db = (unsigned char)sum;
            }
        }
    }
}

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

void wabun1x3(unsigned char *img1, unsigned char *img2, unsigned char *dst, int width, int height)
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

void wabun2x2(unsigned char *img1, unsigned char *img2, unsigned char *dst, int width, int height)
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

void wabun3x3(unsigned char *img1, unsigned char *img2, unsigned char *dst, int width, int height)
{
    unsigned char *pa, *pb, *pc, *pd, *pe, *pf, *pg, *ph, *da, *db;
    int mask = 3;
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
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                // マスク処理 
                for (k = 0, pc = pb - width - ((mask - 1) / 2), pg = pf - width - ((mask - 1) / 2); k < mask; k++, pc += width, pg += width)
                {
                    for (l = 0, pd = pc, ph = pg; l < mask; l++, pd++, ph++)
                    {
                        left = (double)*pd; // １枚目を代入
                        right = (double)*ph; // ２枚目を代入
                            
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

void opticalFlowhori(unsigned char *img1, unsigned char *img2, int wid, int hei, unsigned char *dst)
{
    int mask = 3;
    unsigned char *pa, *pb, *pc, *pd, *pe, *pf, *da, *db;
    int i, j, k;
    double alpha = 0.1;
    double left, right, dx, dtl, dtr, vx;

    for (i = 0, pa = img1, pd = img2, da = dst; i < hei; i++, pa += wid, pd += wid, da += wid)
    {
        for (j = 0, pb = pa, pe = pd, db = da; j < wid; j++, pb++, pe++, db++)
        {
            // マスク処理
            if (j >= (mask - 1) / 2 && j < wid - ((mask - 1) / 2))
            {
                dx = 0;
                dtl = 0;
                dtr = 0;
                for (k = 0, pc = pb - ((mask - 1) / 2), pf = pe - ((mask - 1) / 2); k < mask; k++, pc++, pf++)
                {
                    left = (double)*pc;
                    right = (double)*pf;

                    if (k == 0)
                    {
                        dx += left / (-2);
                        dtl += left / (-2);
                        dtr += right / 2;
                    }
                    else if (k == 1)
                    {
                    }
                    else 
                    {
                        dx += left / 2;
                        dtl += left / (-2);
                        dtr += right / 2;
                    }
                }
                vx = fabs(dtl + dtr) / (fabs(dx) + alpha);

                if (vx >= 0 && vx < 1)
                {
                    *db = 255;
                }
                else
                {
                    *db = 0;
                }
            }
            else
            {
                *db = 0;
            }
        }
    }

}
