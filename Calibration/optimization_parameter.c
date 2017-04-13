/* 最急降下法で最適なパラメーター(平行移動量、回転角)を求める */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define PI 3.141592

void readcoeff(char [], double []);
void readcoordinate(char [], double []);
double fp(double []);
double dfpa(double []); // 2点近似でalphaについて偏微分
double dfpb(double []); // 2点近似でbetaについて偏微分
double dfpg(double []); // 2点近似でgammaについて偏微分
double dfpcx(double []); // 2点近似でcxについて偏微分
double dfpcy(double []); // 2点近似でcyについて偏微分
double dfpcz(double []); // 2点近似でczについて偏微分
void update_x(double [], double); // ベクトルxの更新

double coef_l[11];
double coef_c[11];
double coordinates[12] = {-37, 170, 364, 30, 180, 430, 30, 108.2, 430, -37, 100, 364}; // 70点だから210

int main(void)
{
    char filename[256];
    double x[6]; // 求めるパラメータ：x[0]=α、x[1]=β、x[2]=γ、x[3]=cx、x[4]=cy、x[5]=cz
    double eta = 0.00001; // 学習係数
    double epsilon = 0.000001;
    int i;

    sprintf(filename, "coefficient/coefficient_l.txt");
    readcoeff(filename, coef_l);   // 射影変換の係数の読み込み
    sprintf(filename, "coefficient/coefficient_c.txt");
    readcoeff(filename, coef_c);   // 射影変換の係数の読み込み
    //sprintf(filename, "coordinate/world_coordinate_c.txt");
    //readcoordinate(filename, coordinates);   // 3次元座標の読み込み

    // 初期値：適宜調整必須
    x[0] = 0; // α
    x[1] = 0; // β
    x[2] = 0; // γ
    x[3] = 10; // cx
    x[4] = 0; // cy
    x[5] = 0; // cz

    printf("初期値\n");
    printf("α = %f\nβ = %f\nγ = %f\ncx = %f\ncy = %f\ncz = %f\n", x[0], x[1], x[2], x[3], x[4], x[5]);
    printf("f(x) = %f\n", fp(x));
    printf("計算開始\n");

    i = 1;
    while (1)
    {
        if(fabs(dfpa(x)) < epsilon && fabs(dfpb(x)) < epsilon && fabs(dfpg(x)) < epsilon && fabs(dfpcx(x)) < epsilon && fabs(dfpcy(x)) < epsilon && fabs(dfpcz(x)) < epsilon)
        {
            break;
        }
        else
        {
             // ベクトルxの更新
            update_x(x, eta);
            i++;
        }  
    }

    printf("試行回数：%d\n", i);
    printf("実行結果\n");
    printf("α = %f\nβ = %f\nγ = %f\ncx = %f\ncy = %f\ncz = %f\n", x[0], x[1], x[2], x[3], x[4], x[5]);
    printf("f(x) = %f\n", fp(x));
    printf("dfpa(x) = %f\n", fabs(dfpa(x)));
    printf("dfpb(x) = %f\n", fabs(dfpb(x)));
    printf("dfpg(x) = %f\n", fabs(dfpg(x)));
    printf("dfpcx(x) = %f\n", fabs(dfpcx(x)));
    printf("dfpcy(x) = %f\n", fabs(dfpcy(x)));
    printf("dfpcz(x) = %f\n", fabs(dfpcz(x)));
    printf("\n計算終了\n");

    return 0;
}

void readcoeff(char filename[], double coef[])
{
    FILE *fp;
    char buffer[256];
    int row = 11;
    int i;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("%sを開けません\n", filename);
        exit(1);
    }
    else
    {
        for (i = 0; i < row; i++)
        {
            if (fgets(buffer, 256, fp) != NULL)
            {
                coef[i] = atof(buffer);
            }
        }
    }
    fclose(fp);
}

void readcoordinate(char filename[], double coordinate[])
{
    FILE *fp;
    char buffer[256];
    int num = 210;
    int i;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("%sを開けません\n", filename);
        exit(1);
    }
    else
    {
        for (i = 0; i < num; i++)
        {
            if (fgets(buffer, 256, fp) != NULL)
            {
                coordinate[i] = atof(buffer);
            }
        }
    }
    fclose(fp);
}

// 左と中央の重ね合わせ
double fp(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    double p;
    double x_, y_, z_;
    double s, t, u, v;
    double rad_a, rad_b, rad_g;
    double a, b, c, d, e, f, g, h, i; // 回転行列の各要素
    int num = 4;
    int j, index;

    /* ラジアンに変換 */
    rad_a = x[0] * PI / 180.0;
    rad_b = x[1] * PI / 180.0;
    rad_g = x[2] * PI / 180.0;

     /* 回転行列の要素 */
    a = cos(rad_b)*cos(rad_g);
    b = -1 * cos(rad_b)*sin(rad_g);
    c = sin(rad_b);
    d = cos(rad_a)*sin(rad_g)+(sin(rad_a)*sin(rad_b)*cos(rad_g));
    e = cos(rad_a)*cos(rad_g)-(sin(rad_a)*sin(rad_b)*sin(rad_g));
    f = -1 * sin(rad_a)*cos(rad_b);
    g = sin(rad_a)*sin(rad_g)-(cos(rad_a)*sin(rad_b)*cos(rad_g));
    h = sin(rad_a)*cos(rad_g)+(cos(rad_a)*sin(rad_b)*sin(rad_g));
    i = cos(rad_a)*cos(rad_b);

    p = 0;
    for (j = 0, index = 0; j < num; j++, index += 3)
    {
        // 左カメラの3軸を回転、平行移動
        x_ = a*coordinates[index] + b*coordinates[index + 1] + c*coordinates[index + 2] - x[3];
        y_ = d*coordinates[index] + e*coordinates[index + 1] + f*coordinates[index + 2] - x[4]; 
        z_ = g*coordinates[index] + h*coordinates[index + 1] + i*coordinates[index + 2] - x[5];

        // 画像上での座標を取得
        s = (coef_c[0]*coordinates[index] + coef_c[1]*coordinates[index + 1] + coef_c[2]*coordinates[index + 2] + coef_c[3]) / (coef_c[8]*coordinates[index] + coef_c[9]*coordinates[index + 1] + coef_c[10]*coordinates[index + 2] + 1);
        t = (coef_c[4]*coordinates[index] + coef_c[5]*coordinates[index + 1] + coef_c[6]*coordinates[index + 2] + coef_c[7]) / (coef_c[8]*coordinates[index] + coef_c[9]*coordinates[index + 1] + coef_c[10]*coordinates[index + 2] + 1);

        u = (coef_l[0]*x_ + coef_l[1]*y_ + coef_l[2]*z_ + coef_l[3]) / (coef_l[8]*x_ + coef_l[9]*y_ + coef_l[10]*z_ + 1);
        v = (coef_l[4]*x_ + coef_l[5]*y_ + coef_l[6]*z_ + coef_l[7]) / (coef_l[8]*x_ + coef_l[9]*y_ + coef_l[10]*z_ + 1);

        p += (s - u)*(s - u) + (t - v)*(t - v);
    }

    return p;
}

double dfpa(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[0] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

double dfpb(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[1] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

double dfpg(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[2] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

double dfpcx(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[3] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

double dfpcy(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[4] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

double dfpcz(double x[])
{
    //x[0]=alpha、x[1]=beta、x[2]=gamma、x[3]=cx、x[4]=cy、x[5]=cz
    const double h = FLT_EPSILON;
    double x_[6];

    memcpy(x_, x, sizeof(double) * 6);
    x_[5] += h;

    double y1 = fp(x_);
    double y2 = fp(x);

    return (y1 - y2) / h;
}

void update_x(double x[], double eta)
{
    x[0] -= eta*dfpa(x);
    x[1] -= eta*dfpb(x);
    x[2] -= eta*dfpg(x);
    x[3] -= eta*dfpcx(x);
    x[4] -= eta*dfpcy(x);
    x[5] -= eta*dfpcz(x);
}
