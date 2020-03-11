#include "Simulation.h"

int main(int argc, char const *argv[]) {

  Simulation s = Simulation();

  s.start();
  if(s.manual){
    string input = "";
    int gen = 0;
    cout << "Type 'q' to quit or hit enter to continue to next generation." << endl;
    input = cin.get();
    while(input != "q"){
      cout << "Generation " << gen << ":" << endl;
      s.grid->print();
      s.update();
      cout << endl;
      gen++;
      input = cin.get();
      s.toLower(input);
    }
  }
  else if(s.automatic){
    int gen = 0;
    while(gen < 500){
      cout << "Generation " << gen << ":" << endl;
      s.grid->print();
      s.update();
      if(s.stable > 5){
        cout << "Stabilized environment detected. Simulation complete." << endl;
        break;
      }
      cout << endl;
      gen++;
      s.pause();
    }
  }
  else if(s.toFile){
    int gen = 0;
    while(gen < 500){
      s.oFS << "Generation " << gen << ":" << endl;
      s.grid->print(s.oFS);
      s.update();
      if(s.stable > 5){
        s.oFS << "Stabilized environment detected. Simulation complete." << endl;
        break;
      }
      s.oFS << endl;
      gen++;
    }
  }
  s.end();

  return 0;
}
