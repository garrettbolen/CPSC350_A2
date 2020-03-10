#include "DonutGrid.h"

int DonutGrid::countNeighbors(int r, int c){
  int sum = 0;
  int idx = 0;
  for(int i = -1; i < 2; ++i){
    for(int j = -1; j < 2; ++j){
      if((c + j) < 0 && (r + i) >= 0 && (r + i) < rows){
        idx = flatIndex((r + i), (cols - 1));
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((c + j) > (cols - 1) && (r + i) >= 0 && (r + i) < rows){
        idx = flatIndex((r + i), 0);
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) < 0 && (c + j) >= 0 && (c + j) < cols){
        idx = flatIndex((rows - 1), (c + j));
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) > (rows - 1) && (c + j) >= 0 && (c + j) < cols){
        idx = flatIndex(0, (c + j));
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) < 0 && (c + j) < 0){
        idx = flatIndex((rows - 1), (cols - 1));
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) < 0 && (c + j) > 0){
        idx = flatIndex((rows - 1), 0);
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) > 0 && (c + j) < 0){
        idx = flatIndex(0, (cols - 1));
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else if((r + i) == rows && (c + j) == cols){
        idx = flatIndex(0, 0);
        if(flatGrid[idx] == 'X')
          sum++;
      }
      else{
        idx = flatIndex(r + i, c + j);
        if(flatGrid[idx] == 'X')
          sum++;
      }
    }
  }
  //Removes own cell from sum total if it is alive
  if(myGrid[r][c] == 'X')
    sum--;
  return sum;
}
