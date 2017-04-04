/* 最急降下法で最適なパラメータを求める */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define PI 3.141592

double f(double);
double mf(double, double); // 多変数関数
double df2(double); // 2点近似
double df3(double); // 3点近似
double df5(double); // 5点近似
double pdfx(double, double); // 2点近似でxについて偏微分

int main(void)
{
    double x;
    double alpha = 0.01; // 学習係数
    int iterate = 100; // 反復回数
    double epsilon = 0.000001;
    int i;

    srand48(123L);   // 初期化
    x = 30;
    printf("ステップ 0：a = %f, ", x);
    printf("f(x) = %f\n", f(x));

    /*
    for (i = 1; i < iterate + 1; i++)
    {
        x = x - (alpha * df3(x));
        printf("ステップ %d：a = %f, ", i, x);
        printf("f(x) = %f\n", f(x));
    }
    */

    i = 1;
    while (fabs(df3(x)) > epsilon)
    {
        x = x - (alpha * df3(x));
        printf("ステップ %d：a = %f, ", i, x);
        printf("f(x) = %f\n", f(x));
        i++;
    }

    return 0;
}

double f(double x)
{
    double f;

    f = x*x + 2*x + 1;
    return f;
}

double mf(double x, double y)
{
    double f;

    f = (x * x) + (2 * x) + (y * y * y) + (y * y);
    return f;
}

double df2(double x)
{
    const double h = FLT_EPSILON;
    double y1 = f(x + h);
    double y2 = f(x);

    return (y1 - y2) / h;
}

double df3(double x)
{
    const double h = FLT_EPSILON;
    double y1 = f(x + h);
    double y2 = f(x - h);

    return (y1 - y2) / (2 * h);
}

double df5(double x)
{
    const double h = FLT_EPSILON;
    double y1 = f(x + h);
    double y2 = f(x - h);
    double y3 = f(x + 2 * h);
    double y4 = f(x - 2 * h);

    return ( y4 - 8 * y2 + 8 * y1 - y3 ) / ( 12 * h );
}

double pdfx(double x, double y)
{
    const double h = FLT_EPSILON;
    double y1 = mf(x + h, y);
    double y2 = mf(x, y);

    return (y1 - y2) / h;
}
