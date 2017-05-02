/*  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592 // 円周率

int main(void)
{
    double a, b, c; // 3辺の長さ
    double ha, hb, hc; // 底辺からの高さ
    double A, B, C; // 角度
    double S; // 面積
    double s;
    double l, x, z;
    double left = 187;

    a = 370; // ２つのレーダー距離計の距離
    printf("AP = \n");
    scanf("%lf", &c);
    printf("BP = \n");
    scanf("%lf", &b);

    // 入力値が数字であるかのチェックを省く    

    s = (a + b + c) / 2;
    S = sqrt(s * (s - a) * (s - b) * (s - c));
    ha = 2 * S / a;

    if (a >= b && a >=  c)
    {
        B = asin(ha / c) * 180 / PI;
        C = asin(ha / b) * 180 / PI;
        A = 180 - (B + C);
    }
    else if (b >= a && b >= c)
    {
        hb = 2 * S / b;
        C = asin(hb / a) * 180 / PI;
        A = asin(hb / c) * 180 / PI;
        B = 180 - (A + C);
    }
    else if (c >= a && c >= b)
    {
        hc = 2 * S / c;
        A = asin(hc / b) * 180 / PI;
        B = asin(hc / a) * 180 / PI;
        C = 180 - (A + B);
    }
    else
    {
    }

    l = sqrt((c * c) - (ha * ha));
    if (l <= left)
    {
        x = (left - l) * (-1);
    }
    else
    {
        x = l - left;
    }

    printf("l = %f\n", l);
    printf("X座標：%f\n", x);
    printf("Z座標：%f\n", ha);

    printf("角A：%f度\n", round(A));
    printf("角B：%f度\n", round(B));
    printf("角C：%f度\n", round(C));
    printf("高さh：%f\n", ha);
    printf("面積S：%f\n", S);

    return 0;
}
