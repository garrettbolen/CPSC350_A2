#include "DonutGrid.h"
#include "ClassicGrid.h"
#include "MirrorGrid.h"
#include <exception>

class Simulation{
public:
  Simulation();
  ~Simulation();
  void start();
  void update();
  bool checkStable();
  void pause();

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
  bool automatic;
  bool toFile;
  int stable;


};
