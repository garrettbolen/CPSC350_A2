#include "ClassicGrid.h"

//This is the classic version of countNeighbors
int ClassicGrid::countNeighbors(int r, int c){
  int sum = 0;
  int idx = 0;
  for(int i = -1; i < 2; ++i){
    for(int j = -1; j < 2; ++j){
      //This if statement essentially checks if the location is off the grid and ignores it if so
      if((r + i) < 0 || (c + j) < 0 || (r + i) >= rows || (c + j) >= cols)
        continue;
      //Otherwise, it takes the flatIndex of the coordinate and increments sum if its a cell
      else{
        idx = flatIndex((r + i), (c + j));
        if(flatGrid[idx] == 'X')
          sum++;
      }
    }
  }
  //Decrements sum is the coordinate checked is a living cell
  if(myGrid[r][c] == 'X')
    sum--;
  return sum;
}
