/* 最急降下法で最適なパラメーター(平行移動量、回転角)を求める */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define PI 3.141592

double fp(double, double, double, double, double, double);
double dfpa(double, double, double, double, double, double); // 2点近似でalphaについて偏微分
double dfpb(double, double, double, double, double, double); // 2点近似でbetaについて偏微分
double dfpg(double, double, double, double, double, double); // 2点近似でgammaについて偏微分
double dfpsx(double, double, double, double, double, double); // 2点近似でsxについて偏微分
double dfpsy(double, double, double, double, double, double); // 2点近似でsyについて偏微分
double dfpsz(double, double, double, double, double, double); // 2点近似でszについて偏微分

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
    while (fabs(dfpa(x)) > epsilon)
    {
        x = x - (alpha * df3(x));
        printf("ステップ %d：a = %f, ", i, x);
        printf("f(x) = %f\n", f(x));
        i++;
    }

    return 0;
}

// 左と中央の重ね合わせ
double fp(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    double p;
    double x, y, z, x_, y_, z_;
    double s, t, u, v;
    double rad_a, rad_b, rad_g;
    double a, b, c, d, e, f, g, h, i; // 回転行列の各要素
    double coef_l[11];
    double coef_c[11];

    x = 10;
    y = 10;
    z = 10;

    /* ラジアンに変換 */
    rad_a = sita * PI / 180.0;
    rad_b = fai * PI / 180.0;
    rad_g = psi * PI / 180.0;

     /* 回転行列の要素 */
    a = cos(rad_b)*cos(rad_g);
    b = -1 * cos(rad_b)*sin(rad_g);
    c = sin(rad_b);
    d = cos(rad_a)*sin(rad_g)+(sin(rad_a)*sin(rad_b)*cos(rad_g));
    e = cos(rad_a)*cos(rad_g)-(sin(rad_a)*sin(rad_b)*sin(rad_g));
    f = -1 * sin(rad_a)*cos(rad_b);
    g = sin(rad_a)*sin(rad_g)-(cos(rad_a)*sin(rad_b)*cos(rad_g));
    h = (sin(rad_a)*cos(rad_g)+(cos(rad_a)*sin(rad_b)*sin(rad_g));
    i = cos(rad_a)*cos(rad_b);

    x_ = a*x + b*y + c*z - sx*a - sy*b - sz*c + sx;
    y_ = d*x + e*y + f*z - sx*d - sy*e - sz*f + sy; 
    z_ = g*x + h*y + i*z - sx*g - sy*h - sz*i + sz;

    u = (coef_l[0]*x_ + coef_l[1]*y_ +coef_l[2]*z_ + coef_l[3]) / (coef_l[8]*x_ + coef_l[9]*y_ +coef_l[10]*z_ + 1);
    v = (coef_l[4]*x_ + coef_l[5]*y_ +coef_l[6]*z_ + coef_l[7]) / (coef_l[8]*x_ + coef_l[9]*y_ +coef_l[10]*z_ + 1);

    s = (coef_c[0]*x + coef_c[1]*y +coef_c[2]*z + coef_c[3]) / (coef_c[8]*x + coef_c[9]*y +coef_c[10]*z + 1);
    t = (coef_c[4]*x + coef_c[5]*y +coef_c[6]*z + coef_c[7]) / (coef_c[8]*x + coef_c[9]*y +coef_c[10]*z + 1);

    p = fabs(s - u) + fabs(t - v);

    return p;
}

double dfpa(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha + h, beta, gamma, sx, sy, sz);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}

double dfpb(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha, beta + h, gamma, sx, sy, sz);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}

double dfpg(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha, beta, gamma + h, sx, sy, sz);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}

double dfpsx(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha, beta, gamma, sx + h, sy, sz);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}

double dfpsy(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha, beta, gamma, sx, sy + h, sz);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}

double dfpsz(double alpha, double beta, double gamma, double sx, double sy, double sz)
{
    const double h = FLT_EPSILON;
    double y1 = fp(alpha, beta, gamma, sx, sy, sz + h);
    double y2 = fp(alpha, beta, gamma, sx, sy, sz);

    return (y1 - y2) / h;
}
