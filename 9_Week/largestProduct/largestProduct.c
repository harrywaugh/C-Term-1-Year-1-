#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define GRID_SIZE 20
#define FILE_NAME "grid.txt"
#define MAX_SIZE 100

//Reads in 2D Array from text file
void readGrid(int **grid){
  int j=0;
  char line[MAX_SIZE];
  char linep[GRID_SIZE*3];

  for(int i=0; i < GRID_SIZE*3; i+=3){
    linep[i]=*"%";
    linep[i+1]=*"d";
    if(i<57){
      linep[i+2]=*" ";
    }
  }
  FILE *in = fopen(FILE_NAME, "r");
  while (! feof(in) && fgets(line, MAX_SIZE, in) != NULL && j< GRID_SIZE) {
    sscanf(line, linep, &grid[0][j], &grid[1][j], &grid[ 2][j], &grid[ 3][j], &grid[ 4][j], &grid[ 5][j],
            &grid[ 6][j], &grid[ 7][j], &grid[ 8][j], &grid[ 9][j], &grid[ 10][j], &grid[ 11][j],
            &grid[ 12][j], &grid[ 13][j], &grid[ 14][j], &grid[ 15][j], &grid[ 16][j], &grid[ 17][j],
            &grid[ 18][j], &grid[ 19][j]);
    j++;
  }
  //PRINT 2D ARRAY
  /*
  for(j=0; j< GRID_SIZE; j++){
    for(int i=0; i< GRID_SIZE; i++){
      printf("%d ",  grid[i][j]);
    }
    printf("\n");
  }*/
  fclose(in);
}

int horizontalProduct(int **grid){
  int largestProduct=0;
  for(int i = 0; i < GRID_SIZE; i++){
    for(int j=0; j+3 < GRID_SIZE; j++){
      int currentProduct = grid[i][j]*grid[i][j+1]*grid[i+2][j]*grid[i+3][j];
      if(largestProduct < currentProduct){
        largestProduct = currentProduct;
      }
    }
  }
  return largestProduct;
}

int main(int argc, char *argv[argc]){
  //Initiatlise 2D array, allocate memory
  int **grid;
  grid=(int**)malloc(sizeof(int*)*GRID_SIZE);
  for(int i = 0; i < GRID_SIZE; i++){
    grid[i]=(int*)malloc(sizeof(int)*GRID_SIZE);
  }

  readGrid(grid);
  printf("Largest Horizontal Product: %d\n", horizontalProduct(grid));

  //Free memory allocated for 2D array
  for(int i = 0; i < GRID_SIZE; i++){
    free(grid[i]);
  }
  free(grid);
  return 0;
}
