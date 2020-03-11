#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Grid{
public:
  Grid(int r, int c, float density);
  Grid(string filename);
  ~Grid();

  void init(int r, int c);
  void print();
  void print(ofstream& oFS);
  int flatIndex(int i, int j);
  void updateFlatGrid();
  bool equals(Grid* grid);
  virtual int countNeighbors(int i, int j){}


  int rows;
  int cols;
  char* flatGrid;
  char** myGrid;
  float popDensity;

};
