#include "Grid.h"

class ClassicGrid : public Grid{
public:
  ClassicGrid(int r, int c, float density) : Grid(r, c, density){}
  ClassicGrid(string filename) : Grid(filename){}

  int countNeighbors(int r, int c);
};
