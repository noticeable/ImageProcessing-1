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
double pdf2(double, double); // 2点近似でxについて偏微分

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
    double y;

    y = (x - 1) * (x - 1) * (x - 1);

    return y;
}

// 左と中央の重ね合わせ
double fp(double sita, double fai, double psi, double sx, double sy, double sz)
{
    double p;
    double x, y, z, x_, y_, z_;
    double s, t, u, v;
    double rad_s, rad_f, rad_p;
    double coef_l[11];
    double coef_c[11];

    x = 10;
    y = 10;
    z = 10;

    rad_s = sita * PI / 180.0;
    rad_f = fai * PI / 180.0;
    rad_p = psi * PI / 180.0;

    x_ = (x*cos(rad_f)*cos(rad_p)) - (y*cos(rad_f)*sin(rad_p)) + (z*sin(rad_f)) + sx;
    y_ = (x*((cos(rad_s)*sin(rad_p))+(sin(rad_s)*sin(rad_f)*cos(rad_p)))) + (y*((cos(rad_s)*cos(rad_p))-(sin(rad_s)*sin(rad_f)*sin(rad_p)))) - (z*sin(rad_s)*cos(rad_f)) + sy;
    z_ = (x*((sin(rad_s)*sin(rad_p))-(cos(rad_s)*sin(rad_f)*cos(rad_p)))) + (y*((sin(rad_s)*cos(rad_p))+(cos(rad_s)*sin(rad_f)*sin(rad_p)))) + (z*cos(rad_s)*cos(rad_f)) + sz;

    u = (coef_l[0]*x_ + coef_l[1]*y_ +coef_l[2]*z_ + coef_l[3]) / (coef_l[8]*x_ + coef_l[9]*y_ +coef_l[10]*z_ + 1);
    v = (coef_l[4]*x_ + coef_l[5]*y_ +coef_l[6]*z_ + coef_l[7]) / (coef_l[8]*x_ + coef_l[9]*y_ +coef_l[10]*z_ + 1);

    s = (coef_c[0]*x + coef_c[1]*y +coef_c[2]*z + coef_c[3]) / (coef_c[8]*x + coef_c[9]*y +coef_c[10]*z + 1);
    t = (coef_c[4]*x + coef_c[5]*y +coef_c[6]*z + coef_c[7]) / (coef_c[8]*x + coef_c[9]*y +coef_c[10]*z + 1);

    p = fabs(s - u) + fabs(t - v);

    return p;
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
