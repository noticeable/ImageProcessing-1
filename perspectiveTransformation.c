#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "perspectiveTransformation.h"

void perspectiveTrans2d(double A[], unsigned char *img, unsigned char *dst, int hei, int wid)
{
    unsigned char *pa, *pb, *pc;
    int band = 3;
    int i, j, k; // i, jは変換後の座標
    double u, v, ux, vy, int_number;
    int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;

    // 変換後座標に対応する変換前の座標を求める
    // 補間法：Bi-linear

    for (i = 0, pa = dst; i < hei; i++, pa += wid * band)
    {
        for (j = 0, pb = pa; j < wid; j++, pb += band)
        {
            u = ((A[0] * j) + (A[1] * i) + A[2]) / ((A[6] * j) + (A[7] * i) + 1);
            v = ((A[3] * j) + (A[4] * i) + A[5]) / ((A[6] * j) + (A[7] * i) + 1);

            if (u > 0 && u < wid - 1 && v > 0 && v < hei - 1) // 画像の淵に点がないとき
            {
                Ax = (int)floor(u);
                Ay = (int)floor(v);
                Bx = (int)floor(u + 1);
                By = (int)floor(v);
                Cx = (int)floor(u + 1);
                Cy = (int)floor(v + 1);
                Dx = (int)floor(u);
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == 0 || u == wid && v == 0 || v == hei) // 四角形の4点のうちのどれか
            {
                Ax = (int)u;
                Ay = (int)v;
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == 0 && v > 0 && v < hei - 1) // 線分AD上に点があるとき
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == wid - 1 && v > 0 && v < hei - 1) // 線分BC上に点があるとき
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u > 0 && u < wid - 1 && v == 0) // 線分AB上に点があるとき
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);;
                By = (int)v;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u > 0 && u < wid - 1 && v == hei - 1) // 線分DC上に点があるとき
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);
                By = (int)v;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
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
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }

            for (k = 0, pc = pb; k < band; k++, pc++)
            {
                if (u >= 0 && u <= wid - 1 && v >= 0 && v <= hei - 1)
                {
                    *pc = (unsigned char)((img[(Ay*wid*band) + (Ax*band) + k] * (1 - ux) * (1 - vy)) + (img[(By*wid*band) + (Bx*band) + k] * ux * (1 - vy)) + (img[(Dy*wid*band) + (Dx*band) + k] * (1 - ux) * vy) + (img[(Cy*wid*band) + (Cx*band) + k] * ux * vy));
                }
                else
                {
                    *pc = 0;
                }
            }
        }
    }
}

void perspectiveTrans2d_two(double A_l[], unsigned char imgL*, unsigned char *dstL, double A_r[], unsigned char *imgR, unsigned char *dstR)
{
    unsigned char *pa, *pb, *pc, *pd, *pe, *pf;
    int band = 3;
    int i, j, k; // i, jは変換後の座標
    double u, v, ux, vy, s, t, sx, ty, int_number;
    int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, As, At, Bs, By, Cs, Ct, Ds, Dt;

    // 変換後座標に対応する変換前の座標を求める
    // 補間法：Bi-linear

    for (i = 0, pa = dstL, pd = dstR; i < hei; i++, pa += wid * band, pd += wid * band)
    {
        for (j = 0, pb = pa, pe = pd; j < wid; j++, pb += band, pe += band)
        {
            u = ((A_l[0] * j) + (A_l[1] * i) + A_l[2]) / ((A_l[6] * j) + (A_l[7] * i) + 1);
            v = ((A_l[3] * j) + (A_l[4] * i) + A_l[5]) / ((A_l[6] * j) + (A_l[7] * i) + 1);

            s = ((A_r[0] * j) + (A_r[1] * i) + A_r[2]) / ((A_r[6] * j) + (A_r[7] * i) + 1);
            t = ((A_r[3] * j) + (A_r[4] * i) + A_r[5]) / ((A_r[6] * j) + (A_r[7] * i) + 1);
            
            //----------------------------1枚目の処理----------------------------------------------  
            if (u > 0 && u < wid - 1 && v > 0 && v < hei - 1) // 画像の淵に点がないとき
            {
                Ax = (int)floor(u);
                Ay = (int)floor(v);
                Bx = (int)floor(u + 1);
                By = (int)floor(v);
                Cx = (int)floor(u + 1);
                Cy = (int)floor(v + 1);
                Dx = (int)floor(u);
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == 0 || u == wid && v == 0 || v == hei) // 四角形の4点のうちのどれか
            {
                Ax = (int)u;
                Ay = (int)v;
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == 0 && v > 0 && v < hei - 1) // 線分AD上に点があるとき
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u == wid - 1 && v > 0 && v < hei - 1) // 線分BC上に点があるとき
            {
                Ax = (int)u;
                Ay = (int)floor(v);
                Bx = (int)0;
                By = (int)0;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)u;
                Dy = (int)floor(v + 1);
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u > 0 && u < wid - 1 && v == 0) // 線分AB上に点があるとき
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);;
                By = (int)v;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            else if (u > 0 && u < wid - 1 && v == hei - 1) // 線分DC上に点があるとき
            {
                Ax = (int)floor(u);
                Ay = (int)v;
                Bx = (int)floor(u + 1);
                By = (int)v;
                Cx = (int)0;
                Cy = (int)0;
                Dx = (int)0;
                Dy = (int)0;
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
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
                ux = modf(u, &int_number);
                vy = modf(v, &int_number);
            }
            //------------------------1枚目の処理------------------------------------------------------------
 
            // -----------------------2枚目の処理------------------------------------------------------------
            if (s > 0 && s < wid - 1 && t > 0 && t < hei - 1) // 画像の淵に点がないとき
            {
                As = (int)floor(s);
                At = (int)floor(t);
                Bs = (int)floor(s + 1);
                Bt = (int)floor(t);
                Cs = (int)floor(s + 1);
                Ct = (int)floor(t + 1);
                Ds = (int)floor(s);
                Dt = (int)floor(t + 1);
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else if (s == 0 || s == wid && t == 0 || t == hei) // 四角形の4点のうちのどれか
            {
                As = (int)s;
                At = (int)t;
                Bs = (int)0;
                Bt = (int)0;
                Cs = (int)0;
                Ct = (int)0;
                Ds = (int)0;
                Dt = (int)0;
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else if (s == 0 && t > 0 && t < hei - 1) // 線分AD上に点があるとき
            {
                As = (int)s;
                At = (int)floor(t);
                Bs = (int)0;
                Bt = (int)0;
                Cs = (int)0;
                Ct = (int)0;
                Ds = (int)s;
                Dt = (int)floor(t + 1);
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else if (s == wid - 1 && t > 0 && t < hei - 1) // 線分BC上に点があるとき
            {
                As = (int)s;
                At = (int)floor(t);
                Bs = (int)0;
                Bt = (int)0;
                Cs = (int)0;
                Ct = (int)0;
                Ds = (int)s;
                Dt = (int)floor(t + 1);
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else if (s > 0 && s < wid - 1 && t == 0) // 線分AB上に点があるとき
            {
                As = (int)floor(s);
                At = (int)t;
                Bs = (int)floor(s + 1);;
                Bt = (int)t;
                Cs = (int)0;
                Ct = (int)0;
                Ds = (int)0;
                Dt = (int)0;
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else if (s > 0 && s < wid - 1 && t == hei - 1) // 線分DC上に点があるとき
            {
                As = (int)floor(u);
                At = (int)v;
                Bs = (int)floor(u + 1);
                Bt = (int)v;
                Cs = (int)0;
                Ct = (int)0;
                Ds = (int)0;
                Dt = (int)0;
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            else
            {
                As = (int)floor(s);
                At = (int)floor(t);
                Bs = (int)floor(s + 1);
                Bt = (int)floor(t);
                Cs = (int)floor(s + 1);
                Ct = (int)floor(t + 1);
                Ds = (int)floor(s);
                Dt = (int)floor(t + 1);
                sx = modf(s, &int_number);
                ty = modf(t, &int_number);
            }
            //------------------------1枚目の処理------------------------------------------------------------
            
            for (k = 0, pc = pb, pf = pe; k < band; k++, pc++, pf++)
            {
                // 1枚目の処理
                if (u >= 0 && u <= wid - 1 && v >= 0 && v <= hei - 1)
                {
                    *pc = (unsigned char)((imgL[(Ay*wid*band) + (Ax*band) + k] * (1 - ux) * (1 - vy)) + (imgL[(By*wid*band) + (Bx*band) + k] * ux * (1 - vy)) + (imgL[(Dy*wid*band) + (Dx*band) + k] * (1 - ux) * vy) + (imgL[(Cy*wid*band) + (Cx*band) + k] * ux * vy));
                }
                else
                {
                    *pc = 0;
                }

                // 2枚目の処理
                if (s >= 0 && s <= wid - 1 && t >= 0 && t <= hei - 1)
                {
                    *pf = (unsigned char)((imgR[(At*wid*band) + (As*band) + k] * (1 - sx) * (1 - ty)) + (imgR[(Bt*wid*band) + (Bs*band) + k] * sx * (1 - ty)) + (imgR[(Dt*wid*band) + (Ds*band) + k] * (1 - sx) * ty) + (imgR[(Ct*wid*band) + (Cs*band) + k] * sx * ty));
                }
                else
                {
                    *pf = 255;
                }

            }
        }
    }
}
