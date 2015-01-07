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
               
    double nHistogram[256];         //灰度直方图  
    double dVariance[256];          //类间方差  
    int N = height*width;           //总像素数  
    for(int i=0; i<256; i++) {  
        nHistogram[i] = 0.0;  
        dVariance[i] = 0.0;  
    }  
    
    for(int i = 0; i < height; i++) 
        for(int f = 0; f < width; f++)
            nHistogram[ G[i][f] ] += 1;     //建立直方图   
            
    double Pa=0.0;      //背景出现概率  
    double Pb=0.0;      //目标出现概率  
    double Wa=0.0;      //背景平均灰度值  
    double Wb=0.0;      //目标平均灰度值  
    double W0=0.0;      //全局平均灰度值  
    double dData1=0.0,  dData2=0.0;  
    for(int i = 0; i < 256; i++)     //计算全局平均灰度  
    {  
        nHistogram[i] /= N;  
        W0 += i*nHistogram[i];  
    }  
    for(int i = 0; i < 256; i++)     //对每个灰度值计算类间方差  
    {  
        Pa += nHistogram[i];  
        Pb = 1-Pa;  
        dData1 += i*nHistogram[i];  
        dData2 = W0-dData1;  
        Wa = dData1/Pa;  
        Wb = dData2/Pb;  
        dVariance[i] = (Pa*Pb* pow((Wb-Wa), 2));  
    }  
    //遍历每个方差，求取类间最大方差所对应的灰度值  
    double temp=0.0;  
    int nThreshold;
    for(int i = 0; i < 256; i++)  
    {  
        if(dVariance[i]>temp)  
        {  
            temp = dVariance[i];  
            nThreshold = i;  
        }  
    }
    printf("aim : %d\n", nThreshold);
    for(int i = 0;i < height; i++)
        for(int f = 0;f < width; f++)
            if(R[i][f] < nThreshold)
                R[i][f] = B[i][f] = G[i][f] = 0;
            else 
                R[i][f] = B[i][f] = G[i][f] = 255;    
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
    write("otsu.bmp");
    getchar();
    return 0;
}