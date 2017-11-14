#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void printBin(int denary){
  for( int i = 31; i >= 0; i-- ) {
    printf( "%d", ( denary >> i ) & 1 );
  }
  printf("\n");
}


void printHex(int denary){
  char *hexabet="0123456789ABCDEF";
  for(int i=7; i>=0; i--){
    printf("%c", hexabet[(denary>>(4*i)) & 15]);
  }
  printf("\n");
}

int packRGBA(int red, int green, int blue, int opacity){
  int colours[4]={red, green, blue, opacity};
  int packedInt=0;
  for(int i = 0; i < 4; i++){
    packedInt = packedInt | (colours[i] << (8*(3-i)));
  }
  return packedInt;
}

void unpackRGBA(int packedInt, int colours[4]){
  for(int i=3; i>=0; i--){
    colours[i] = 255 & (packedInt >> (8*(3-i)));
  }
}

int packPixel(int x, int y, int z){
  int pixel=0;
  int dimensions[3]={z, y, x};
  for(int i=0; i<3; i++){
    if(dimensions[i]<0){
      dimensions[i]=dimensions[i] ^ -1024;
    }
    pixel = pixel | (dimensions[i] << 10*i);
  }
  return pixel;
}

void unpackPixel(int packedPixel, int dimensions[3]){
  for(int i=2; i>=0; i--){
    dimensions[i] = 2047 & (packedPixel >> (10*(2-i)));
    if(dimensions[i]>=512){
      dimensions[i]=dimensions[i] | ~(511);
    }
  }
}

int main(int n, char *args[n]){
  setbuf(stdout, NULL);
  if(n==2){
    int dimensions[3]={0, 0, 0};
    printBin(-50); printBin(100); printBin(63); printf("\n");
    unpackPixel(packPixel(-50, 100, 63), dimensions);
    printf("\n");
    printBin(packPixel(-50, 100, 63));
    printf("\n");
    printf("%d\n",dimensions[0]);
    printf("%d\n",dimensions[1]);
    printf("%d\n", dimensions[2]);
    printBin(dimensions[0]);
    printBin(dimensions[1]);
    printBin(dimensions[2]);
  }
  return 0;
}
