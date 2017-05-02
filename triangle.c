/* 3角形の3辺から角度を計算する */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592 // 円周率

int main(void)
{
    double a, b, c; // 3辺の長さ
    double h; // 底辺からの高さ
    double A, B, C; // 角度
    double S; // 面積
    double s;

    printf("値を入力してください\n");
    printf("辺a = ");
    scanf("%lf", &a);
    printf("辺a = %f\n", a);
    printf("辺b = ");
    scanf("%lf", &b);
    printf("辺b = %f\n", b);
    printf("辺c = ");
    scanf("%lf", &c);
    printf("辺c = %f\n", c);

    // 入力値が数字であるかのチェックを省く    

    s = (a + b + c) / 2;
    S = sqrt(s * (s - a) * (s - b) * (s - c));

    if (a >= b && a >=  c)
    {
        h = 2 * S / a;
        B = asin(h / c) * 180 / PI;
        C = asin(h / b) * 180 / PI;
        A = 180 - (B + C);
    }
    else if (b >= a && b >= c)
    {
        h = 2 * S / b;
        C = asin(h / a) * 180 / PI;
        A = asin(h / c) * 180 / PI;
        B = 180 - (A + C);
    }
    else if (c >= a && c >= b)
    {
        h = 2 * S / c;
        A = asin(h / b) * 180 / PI;
        B = asin(h / a) * 180 / PI;
        C = 180 - (A + B);
    }
    else
    {
    }

    printf("角A：%f度\n", round(A));
    printf("角B：%f度\n", round(B));
    printf("角C：%f度\n", round(C));
    printf("高さh：%f\n", h);
    printf("面積S：%f\n", S);

    return 0;
}
