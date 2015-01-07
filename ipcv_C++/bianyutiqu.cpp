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
     for(int i = 0;i < height - 1; i++)
         for(int f = 0;f < width - 1; f++) {
             int ave = R[i][f] + B[i][f] + G[i][f];
             ave /= 3;
             G[i][f] = B[i][f] = R[i][f] = ave;   
         }
         
     for(int i = 0;i < height - 1; i++)
         for(int f = 0;f < width - 1; f++) {
             G[i][f] = B[i][f] = R[i][f] = abs(G[i][f] - G[i+1][f]) + abs(G[i][f] - G[i][f+1]);   
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

int main() {
    Read("normal.bmp");
    
    fun();
    write("bianyuantiqu.bmp");
    getchar();
    return 0;
}