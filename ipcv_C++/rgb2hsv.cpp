#include <stdio.h>
#include <iostream>

using namespace std;

int R[1000][1000];
int B[1000][1000];
int G[1000][1000];
int height;
int width;
unsigned char info[54];
int row_padded;

unsigned char* data = new unsigned char[10000];
     
void Read(char * filename) {
     FILE* f = fopen(filename, "rb");
     
     if(f == NULL)
         throw "Argument Exception";
     
     fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
     // extract image height and width from header
     width = *(int*)&info[18];
     height = *(int*)&info[22];
     cout << endl;
     cout << " Name: " << filename << endl;
     cout << " Width: " << width << endl;
     cout << " Height: " << height << endl;
     row_padded = (width*3 + 3) & (~3);
     
     unsigned char tmp;
     for(int i = 0; i < height; i++) {
         fread(data, sizeof(unsigned char), row_padded, f);
         for(int j = 0; j < width*3; j += 3) {
         // cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
             R[i][j/3] = data[j + 2];
             G[i][j/3] = data[j + 1];
             B[i][j/3] = data[j];
          }
     }
     fclose(f);
}

double hue[1000][1000];
double value[1000][1000];
double saturation[1000][1000];

void hsv() {
     for(int i = 0; i < height; i++)
         for(int f = 0;f < width; f++) {
             double maxx = max(R[i][f], max(G[i][f], B[i][f]) );
             double minn = min(R[i][f], min(G[i][f], B[i][f]) );
             if(maxx == minn) 
                 hue[i][f] = 0;
             if(maxx == R[i][f] && G[i][f] >= B[i][f])
                 hue[i][f] = 60 * ((G[i][f] - B[i][f])/(maxx - minn));
             
             if(maxx == R[i][f] && G[i][f] < B[i][f])
                 hue[i][f] = 60 * ((G[i][f] - B[i][f])/(maxx - minn)) + 360;
             
             if(maxx == G[i][f])
                 hue[i][f] = 60 * ((B[i][f] - R[i][f])/(maxx - minn)) + 120;
             
             if(maxx == B[i][f])
                 hue[i][f] = 60 * ((R[i][f] - G[i][f])/(maxx - minn)) + 240;
                 
             if(0 == maxx)
                 saturation[i][f] = 0;
             else
                 saturation[i][f] = 1 - minn / maxx;
             
             value[i][f] = maxx;
             
         }
}

void write(char * filename) {
     FILE * f = fopen(filename, "wb");
     fwrite(info,  sizeof(unsigned char) ,54, f);
     
     for(int i = 0; i < height; i++) {
         for(int j = 0; j < width*3; j += 3) {
             data[j + 2] = R[i][j/3];
             data[j + 1] = G[i][j/3];
             data[j] = B[i][j/3];
          }
          fwrite(data, sizeof(unsigned char), row_padded, f);
     }
    fclose(f);
}

double Y[1000][1000];
double Cb[1000][1000];
double Cr[1000][1000];

void ycbcr() {
    for(int i = 0;i < height ;i++)
        for(int f = 0;f < width;f ++) {
            Y[i][f] = 0.257*R[i][f] + 0.564*G[i][f] + 0.098*B[i][f] + 16;
            Cb[i][f] = -0.148*R[i][f] - 0.291*G[i][f] + 0.439*B[i][f] + 128;
            Cr[i][f] = 0.439*R[i][f] - 0.368*G[i][f] - 0.071*B[i][f] + 128;
        }
}

int main() {
    Read("normal.bmp");
    
    hsv();
    ycbcr();
    getchar();
    return 0;
}