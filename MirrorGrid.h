#include "Grid.h"

class MirrorGrid : public Grid{
public:
  MirrorGrid(int r, int c, float density) : Grid(r, c, density){}
  MirrorGrid(string filename) : Grid(filename){}

  int countNeighbors(int r, int c);
};
