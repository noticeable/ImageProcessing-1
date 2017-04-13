// 求めたパラメータを使ってキャリブレーションする

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

void readcoeff(char [], double []); // 3次元から2次元への射影変換の係数の読み込み

int main()
{
    char filename[256];
    double coordinate[3];
    double para[6]; // 求めるパラメータ：para[0]=α、para[1]=β、para[2]=γ、para[3]=cx、para[4]=cy、para[5]=cz

    sprintf(filename, "coefficient/coefficient_l.txt");
    readcoeff(filename, coef_l);   // 射影変換の係数の読み込み
    sprintf(filename, "coefficient/coefficient_c.txt");
    readcoeff(filename, coef_c);   // 射影変換の係数の読み込み

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
