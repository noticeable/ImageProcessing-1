// 求めたパラメータを使ってキャリブレーションする

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592
#define WID 1280
#define HEI 640

void readcoeff(char [], double []); // 3次元から2次元への射影変換の係数の読み込み
void calib(double [], double []);

double coef_l[11];
double coef_c[11];

int main()
{
    char filename[256];
    double coordinate[3] = {-37, 170, 364};
    double para[6]; // 求めるパラメータ：para[0]=α、para[1]=β、para[2]=γ、para[3]=cx、para[4]=cy、para[5]=cz

    sprintf(filename, "coefficient/coefficient_l.txt");
    readcoeff(filename, coef_l);   // 射影変換の係数の読み込み
    sprintf(filename, "coefficient/coefficient_c.txt");
    readcoeff(filename, coef_c);   // 射影変換の係数の読み込み

    // 回転量
    para[0] = -0.278; // α
    para[1] = 0.580; // β
    para[2] = -0.713; // γ
    printf("回転角\nα＝%f β＝%f γ＝%f\n", para[0], para[1], para[2]);

    // 3軸の回転
    calib(coordinate, para);
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

void calib(double coordinate[], double para[])
{
    double rad_a, rad_b, rad_g;
    double x_, y_, z_;
    double s, t, u, v, p, q;
    double a, b, c, d, e, f, g, h, i; // 回転行列の各要素

    /* ラジアンに変換 */
    rad_a = para[0] * PI / 180.0;
    rad_b = para[1] * PI / 180.0;
    rad_g = para[2] * PI / 180.0;

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

    // 左カメラの3軸を回転
    x_ = a*coordinate[0] + b*coordinate[1] + c*coordinate[2];
    y_ = d*coordinate[0] + e*coordinate[1] + f*coordinate[2]; 
    z_ = g*coordinate[0] + h*coordinate[1] + i*coordinate[2];

    // 画像上での座標を取得
    s = (coef_c[0]*coordinate[0] + coef_c[1]*coordinate[1] + coef_c[2]*coordinate[2] + coef_c[3]) / (coef_c[8]*coordinate[0] + coef_c[9]*coordinate[1] + coef_c[10]*coordinate[2] + 1);
    t = (coef_c[4]*coordinate[0] + coef_c[5]*coordinate[1] + coef_c[6]*coordinate[2] + coef_c[7]) / (coef_c[8]*coordinate[0] + coef_c[9]*coordinate[1] + coef_c[10]*coordinate[2] + 1);

    // 左画像
    u = (coef_l[0]*x_ + coef_l[1]*y_ + coef_l[2]*z_ + coef_l[3]) / (coef_l[8]*x_ + coef_l[9]*y_ + coef_l[10]*z_ + 1);
    v = (coef_l[4]*x_ + coef_l[5]*y_ + coef_l[6]*z_ + coef_l[7]) / (coef_l[8]*x_ + coef_l[9]*y_ + coef_l[10]*z_ + 1);

    // 左画像 キャリブレーション無し
    p = (coef_l[0]*coordinate[0] + coef_l[1]*coordinate[1] + coef_l[2]*coordinate[2] + coef_l[3]) / (coef_l[8]*coordinate[0] + coef_l[9]*coordinate[1] + coef_l[10]*coordinate[2] + 1);
    q = (coef_l[4]*coordinate[0] + coef_l[5]*coordinate[1] + coef_l[6]*coordinate[2] + coef_l[7]) / (coef_l[8]*coordinate[0] + coef_l[9]*coordinate[1] + coef_l[10]*coordinate[2] + 1);

    printf("左画像(キャリブレーション有)：(%f, %f) キャリブレーション無：(%f, %f)\n", u + (WID / 2), (HEI / 2) - v, p + (WID / 2), (HEI / 2) - q);
    printf("中央画像(%f, %f)\n", s + (WID / 2), (HEI / 2) - t);
}
