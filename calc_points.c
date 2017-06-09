/* 任意の点を通る平面上の4点の3次元座標を求めて、その4点から2次元から2次元への射影変換の係数を求める */
#include <stdio.h>
#include <stdlib.h>

void readcoeff(char [], double []);
void calc_coordinate(double [], double [], double []);

int main()
{
    double x, z; // 任意の点,入力値
    double len = 50; // 任意の点から4点までの水平方向の長さ
    double ABy = 180; // 点A,Bの高さ
    double CDy = 100; // 点C,Dの高さ
    double Al[3]; // 左上 Al[0] = x, Al[1] = y, Al[2] = z (以下同様)
    double Bl[3]; // 右上
    double Cl[3]; // 右下
    double Dl[3]; // 左下
    double Ar[3]; // 左上
    double Br[3]; // 右上
    double Cr[3]; // 右下
    double Dr[3]; // 左下

    /* 任意点の入力 */
    printf("x = (単位:cm)\n");
    scanf("%lf", &x);
    printf("z = (単位:cm)\n");
    scanf("%lf", &z);

    /* 平面上の4点の3次元座標を求める */
    /* X軸(水平方向)とのなす角が45度のとき */
    Al[0] = x - len;
    Al[1] = ABy;
    Al[2] = z - len;
    Bl[0] = x + len;
    Bl[1] = ABy;
    Bl[2] = z + len;
    Cl[0] = x + len;
    Cl[1] = CDy;
    Cl[2] = z + len;
    Dl[0] = x - len;
    Dl[1] = CDy;
    Dl[2] = z - len;

    /* X軸とのなす角が135度のとき */
    Ar[0] = Al[0];
    Ar[1] = Al[1];
    Ar[2] = z + len;
    Br[0] = Bl[0];
    Br[1] = Bl[1];
    Br[2] = z - len;
    Cr[0] = Cl[0];
    Cr[1] = Cl[1];
    Cr[2] = z - len;
    Dr[0] = Dl[0];
    Dr[1] = Dl[1];
    Dr[2] = z + len;

    return 0;
}

void readcoeff(char filename[], double coefficient[])
{
    FILE *fp;
    char buffer[256];
    int row = 11;
    int i;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }
    else
    {
        for (i = 0; i < row; i++)
        {
            if (fgets(buffer, 256, fp) != NULL)
            {
                coefficient[i] = atof(buffer);
            }
        }
    }
    fclose(fp);
}

void calc_coordinate(double coefficient[], double xyz[], double uv[])
{
   // 3次元から2次元への射影変換を行い画像座標(u, v)を計算する
   uv[0] =  
}
