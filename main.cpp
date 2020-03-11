#include "Simulation.h"

int main(int argc, char const *argv[]) {

  Simulation s = Simulation();
  // if(argc < 3)
  //   exit(-1);

  s.start();
  // int i = atoi(argv[1]);
  // int j = atoi(argv[2]);
  //
  // cout << s.grid->countNeighbors(i, j) << endl;
  for(int i = 1; i < 11; ++i){
    cout << "Generation " << i << endl;
    s.update();
    s.grid->print();
    cout << endl;
  }
  s.end();

  return 0;
}
