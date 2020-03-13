#include "Grid.h"

//The DonutGrid class inherits from Grid
class DonutGrid : public Grid{
public:
  DonutGrid(int r, int c, float density) : Grid(r, c, density){}
  DonutGrid(string filename) : Grid(filename){}

  //countNeighbors is defined here with custom rules
  int countNeighbors(int r, int c);
};
