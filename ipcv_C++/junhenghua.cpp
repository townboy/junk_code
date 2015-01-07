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

void fun() {
     for(int i = 0;i < height; i++)
         for(int f = 0;f < width; f++) {
             int ave = G[i][f] + R[i][f] + B[i][f];
             ave /= 3;
             G[i][f] = B[i][f] = R[i][f] = ave;
         }
         
     double num[256];
     
     for(int i = 0 ;i < 256; i++)
         num[i] = 0;
     
     for(int i = 0;i < height; i++)
         for(int f = 0;f < width; f++)
             num[ G[i][f] ] += 1;
     
     for(int i = 0; i < 256; i++) {
         num[i] /= 1.0 * height * width;
         if(i > 0)
              num[i] += num[i-1];
     }
     
     int to[256];
     for(int i = 0;i < 256; i++)
         to[i] = int(255 * num[i] + 0.5);
         
     for(int i = 0;i < height; i++)
         for(int f = 0;f < width; f++)
             R[i][f] = B[i][f] = G[i][f] = to[R[i][f]];
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

int main() {
    Read("normal.bmp");
    
    fun();
    write("junhenghua.bmp");
    getchar();
    return 0;
}