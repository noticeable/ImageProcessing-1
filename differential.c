/* 数値微分を行う */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double f(double);
double df2(double); // 2点近似
double df3(double); // 3点近似
double df5(double); // 5点近似
double mf(double, double); // 多変数関数
double pdf2(double, double); // 2点近似でxについて偏微分

int main(void)
{
    double x = 2;
    double y = 1;

    printf("2点近似：%f\n", df2(x));
    printf("3点近似：%f\n", df3(x));
    printf("5点近似：%f\n", df5(x));

    printf("2点近似でxについて偏微分：%f\n", pdf2(x, y));

    return 0;
}

double f(double x)
{
    double y;

    y = x * x * x * x + (2 * x * x * x);

    return y;
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
    double y3 = f(x + (2 * h));
    double y4 = f(x - (2 * h));

    return (y4 - (8 * y2) + (8 * y1) - y3) / (12 * h);
}

double mf(double x, double y)
{
    double f;

    f = (x * x) + (2 * x) + (y * y * y) + (y * y);
    return f;
}

double pdf2(double x, double y)
{
    const double h = FLT_EPSILON;
    double y1 = mf(x + h, y);
    double y2 = mf(x, y);

    return (y1 - y2) / h;
}
