#include "DonutGrid.h"
#include <exception>

class Simulation{
public:
  Simulation();
  void start();
  void update();
  bool checkStable();
  void end();

  bool isNumber(string s);
  void toLower(string& s);

  Grid* grid;
  Grid* gridCopy;

  ofstream oFS;
  string mode;
  string genType;
  string filename;
  int rows;
  int cols;
  float density;
  bool manual;
  int stable;


};
