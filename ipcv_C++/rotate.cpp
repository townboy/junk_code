#include <stdio.h>
#include <iostream>
#include <math.h>

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

int nR[1000][1000];
int nB[1000][1000];
int nG[1000][1000];

void fun() {
     double coso = cos(0.2);
     double sino = sin(0.2);
     
     memset(nR, 0, sizeof(nR));
     memset(nB, 0, sizeof(nR));
     memset(nG, 0, sizeof(nR));
     for(int i = 0;i < height; i++)
         for(int f = 0;f < width; f++) {
             int x = i * coso + f * sino;
             int y = - i * sino + f * coso;
             nR[x][y] = R[i][f];
             nB[x][y] = B[i][f];
             nG[x][y] = G[i][f]; 
         }
     for(int i = 1;i < height; i++)
         for(int f = 1;f < width; f++) {
             if(0 == nR[i][f]) {
                  nR[i][f] = (nR[i][f + 1] + nR[i][f - 1] + nR[i - 1][f] + nR[i + 1][f]) / 4;
                  nB[i][f] = (nB[i][f + 1] + nB[i][f - 1] + nB[i - 1][f] + nB[i + 1][f]) / 4;
                  nG[i][f] = (nG[i][f + 1] + nG[i][f - 1] + nG[i - 1][f] + nG[i + 1][f]) / 4;
             }
     }
}

void write(char * filename) {
     FILE * f = fopen(filename, "wb");
     fwrite(info,  sizeof(unsigned char) ,54, f);
     
     for(int i = 0; i < height; i++) {
         for(int j = 0; j < width*3; j += 3) {
             data[j + 2] = nR[i][j/3];
             data[j + 1] = nG[i][j/3];
             data[j] = nB[i][j/3];
          }
          fwrite(data, sizeof(unsigned char), row_padded, f);
     }
    fclose(f);
}

int main() {
    Read("normal.bmp");
    
    fun();
    write("rotate.bmp");
    getchar();
    return 0;
}