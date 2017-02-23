#ifndef IMGPROC_H
#define IMGPROC_H

void grayscale(unsigned char *, unsigned char *, int, int);
void composite(unsigned char *, unsigned char *, int, int, unsigned char *);
void wabun1x3(unsigned char *, unsigned char *, unsigned char *, int, int);
void wabun2x2(unsigned char *, unsigned char *, unsigned char *, int, int);
void wabun3x3(unsigned char *, unsigned char *, unsigned char *, int, int);

#endif
