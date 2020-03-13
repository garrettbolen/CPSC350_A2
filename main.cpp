#include "Simulation.h"

int main(int argc, char const *argv[]) {

  //A new simulation is created when the program is run
  Simulation s;

  //the start method is called to gather info for the game conditions
  s.start();

  //This string of if-else conditions will dictate where the game is outputted to

  //If manual is true, then manual control will activate
  if(s.manual){
    string input = "";
    int gen = 0;
    cout << "Type 'q' to quit or hit enter to continue to next generation." << endl;
    input = cin.get();
    //This will loop for as long as the user decides by typing 'q' when done
    while(input != "q"){
      cout << "Generation " << gen << ":" << endl;
      //The grid's info is printed for that generation
      s.grid->print();
      //The update method is called to cycle to the next generation
      s.update();
      cout << endl;
      gen++;
      input = cin.get();
      s.toLower(input);
    }
  }
  //This block represents automatic control and works similar to the one before
  else if(s.automatic){
    int gen = 0;
    //Gen < 500 acts as a hard cap for the total number of generations
    while(gen < 500){
      cout << "Generation " << gen << ":" << endl;
      s.grid->print();
      s.update();
      //If the simulation is stable for more than 5 iterations, the simulation ends
      if(s.stable > 5){
        cout << "Stabilized environment detected. Simulation complete." << endl;
        break;
      }
      cout << endl;
      gen++;
      //The pause method is called to allow the user to see each generation
      s.pause();
    }
  }
  //This block represents output to a file
  else if(s.toFile){
    int gen = 0;
    //Once again, gen < 500 acts as a hard cap so it doesn't loop indefinitely
    while(gen < 500){
      //This entire block works almost identical to automatic except it outputs to a file, not the console
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
  //The destructor for simulation is implicitly called here, deleting all member variables
  return 0;
}
