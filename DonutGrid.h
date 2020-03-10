#include "Grid.h"

class DonutGrid : public Grid{
public:
  DonutGrid(int r, int c, float density) : Grid(r, c, density){}
  DonutGrid(string filename) : Grid(filename){}

  int countNeighbors(int r, int c);
};
