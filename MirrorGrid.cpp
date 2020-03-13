#include "MirrorGrid.h"

int MirrorGrid::countNeighbors(int r, int c){
  int sum = 0;
  int idx = 0;

  //corners - (0,0)
  if(flatIndex(r, c) == 0){
    idx = flatIndex(0,0);
    if(flatGrid[idx] == 'X'){
      sum += 3;
    }
  } // (0,farthest right) corner
  else if(flatIndex(r,c) == flatIndex(0, cols - 1)){
    idx = flatIndex(0, (cols - 1));
    if(flatGrid[idx] == 'X'){
      sum += 3;
    }
  } // (bottom most,0) corner
  else if(flatIndex(r,c) == flatIndex((rows - 1), 0)){
    idx = flatIndex((rows - 1),0);
    if(flatGrid[idx] == 'X'){
      sum += 3;
    }
  } // (bottom most, farthest right) corner
  else if(flatIndex(r,c) == flatIndex((rows - 1), (cols - 1))){
    idx = flatIndex((rows - 1),(cols - 1));
    if(flatGrid[idx] == 'X'){
      sum += 3;
    }
  }

  //loop countNeighbors
  for(int i = -1; i < 2; ++i){
    for(int j = -1; j < 2; ++j){

      //top edge, not including corners
      if(((r + i) <= 0) && ((c + j) > 0) && ((c + j) < (cols-1))){
        idx = flatIndex(0, (c + j));
        if(flatGrid[idx] == 'X'){
          sum++;
          // check corners to mirror and add to sum
          if((r+i) == 0 && (c+j) == (cols - 1) || (r+i) == 0 && (c+j) == 0){
            idx = flatIndex(0, (cols - 1));
            idx = flatIndex(0,0);
            if(flatGrid[idx] == 'X'){
              sum++;
            }
          }
        }
      } // bottom edge, not including corners
      else if((r + i) < rows && (c + j) >= 0 && (c + j) <= (cols)){
        idx = flatIndex((r + i), (c + j));
        if(flatGrid[idx] == 'X'){
          sum++;
          // check corners to mirror and add to sum
          if((r+i) == (rows - 1) && (c+j) == (cols - 1) || (r+i) == (rows - 1) && (c+j) == 0){
            idx = flatIndex((rows - 1), (cols - 1));
            idx = flatIndex((rows-1),0);
            if(flatGrid[idx] == 'X'){
              sum++;
            }
          }
        }
      } // left edge, not including corners
      else if((c + j) <= 0 && (r + i) >= 0 && (r + i) < (rows)){
        idx = flatIndex((r + i), 0);
        if(flatGrid[idx] == 'X'){
          sum++;
          // check corners to mirror and add to sum
          if((r+i) == 0 && (c+j) == (cols - 1) || (r+i) == 0 && (c+j) == 0){
            idx = flatIndex(0, (cols - 1));
            idx = flatIndex(0,0);
            if(flatGrid[idx] == 'X'){
              sum++;
            }
          }
        }
      } // right edge, not including corners
      else if((c + j) <= (cols) && (r + i) >= 0 && ((r + i) < (rows - 1))){
        idx = flatIndex((r + i), (c + j));
        if(flatGrid[idx] == 'X'){
          sum++;
          // check corners to mirror and add to sum
          if((r+i) == (rows - 1) && (c+j) == (cols - 1) || (r+i) == (rows - 1) && (c+j) == 0){
            idx = flatIndex((rows - 1), (cols - 1));
            idx = flatIndex((rows-1),0);
            if(flatGrid[idx] == 'X'){
              sum++;
            }
          }
        }
      } // out of bounds
      else if((r + i) < 0 || (r + i) >= rows || (c + j) < 0 || (c + j) >= cols){
        continue;
      }

      //standard
      else{
        idx = flatIndex(r + i, c + j);
        if(flatGrid[idx] == 'X'){
          sum++;
        }
      }
    }
  }

  if(myGrid[r][c] == 'X')
    sum--;
  return sum;
}
