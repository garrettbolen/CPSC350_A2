#include "DonutGrid.h"
#include "Simulation.h"

int main(int argc, char const *argv[]) {
  DonutGrid g = DonutGrid("map.txt");
  cout << g.countNeighbors(2, 5) << endl;
  g.print();
  return 0;
}
