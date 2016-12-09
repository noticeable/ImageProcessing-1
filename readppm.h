#define MAX_BUFFERSIZE 1024
#define BAN 3

int wid, hei;

void readppm(char filename[], unsigned char *img);

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

    // Check the file type 'P6'
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if(buffer[0] != 'P' || buffer[1] != '6')
    {
        printf("Not P6!!\n");
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

    fread(img, sizeof(unsigned char), wid * hei * BAN, fp);
    fclose(fp);
}
