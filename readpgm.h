#ifndef READPGM_H
#define READPGM_H 

#define MAX_BUFFERSIZE 1024

int wid, hei;

void readppm(char filename[], unsigned char *img)
{
    FILE *fp;
    char buffer[MAX_BUFFERSIZE];
    int max_color;

    if((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Not Open %s\n", filename);
        exit(1);
    }

    // Check the file type 'P5'
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if(buffer[0] != 'P' || buffer[1] != '5')
    {
        printf("Not P5!!\n");
        exit(1);
    }

    // Input of wid and hei
    wid = 0;
    hei = 0;
    while(wid == 0 || hei == 0)
    {
        fgets(buffer, MAX_BUFFERSIZE, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d %d", &wid, &hei);
        }
    }

    // Input of max_color
    max_color = 0;
    while(max_color == 0)
    {
        fgets(buffer, MAX_BUFFERSIZE, fp);
        if(buffer[0] != '#')
        {
            sscanf(buffer, "%d", &max_color);
        }
    }

    fread(img, sizeof(unsigned char), wid * hei, fp);
    fclose(fp);
}

#endif
