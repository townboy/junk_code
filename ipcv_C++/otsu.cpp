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
               
    double nHistogram[256];         //�Ҷ�ֱ��ͼ  
    double dVariance[256];          //��䷽��  
    int N = height*width;           //��������  
    for(int i=0; i<256; i++) {  
        nHistogram[i] = 0.0;  
        dVariance[i] = 0.0;  
    }  
    
    for(int i = 0; i < height; i++) 
        for(int f = 0; f < width; f++)
            nHistogram[ G[i][f] ] += 1;     //����ֱ��ͼ   
            
    double Pa=0.0;      //�������ָ���  
    double Pb=0.0;      //Ŀ����ָ���  
    double Wa=0.0;      //����ƽ���Ҷ�ֵ  
    double Wb=0.0;      //Ŀ��ƽ���Ҷ�ֵ  
    double W0=0.0;      //ȫ��ƽ���Ҷ�ֵ  
    double dData1=0.0,  dData2=0.0;  
    for(int i = 0; i < 256; i++)     //����ȫ��ƽ���Ҷ�  
    {  
        nHistogram[i] /= N;  
        W0 += i*nHistogram[i];  
    }  
    for(int i = 0; i < 256; i++)     //��ÿ���Ҷ�ֵ������䷽��  
    {  
        Pa += nHistogram[i];  
        Pb = 1-Pa;  
        dData1 += i*nHistogram[i];  
        dData2 = W0-dData1;  
        Wa = dData1/Pa;  
        Wb = dData2/Pb;  
        dVariance[i] = (Pa*Pb* pow((Wb-Wa), 2));  
    }  
    //����ÿ�������ȡ�����󷽲�����Ӧ�ĻҶ�ֵ  
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