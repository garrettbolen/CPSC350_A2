#include "Simulation.h"

Simulation::Simulation(){
  stable = 0;
  manual = false;
  automatic = false;
  toFile = false;
}
Simulation::~Simulation(){
  delete grid;
  delete gridCopy;
  oFS.close();
}

void Simulation::start(){
  string typeInput = "";
  string modeInput = "";
  string fileInput = "";
  string colInput = "";
  string rowInput = "";
  string densityInput = "";
  string gameControl = "";
  string gameOutput = "";

  cout << "Welcome to the Game of Life. Type 'r' for a random map or 'f' for a map file input: " << endl;
  do{
    cin >> typeInput;
    toLower(typeInput);
    if(typeInput == "r"){
      genType = "r";
      cout << "Enter the dimensions for your grid below: " << endl;

      cout << "Rows: ";
      while(true){
        cin >> rowInput;
        if(isNumber(rowInput)){
          rows = stoi(rowInput);
          break;
        }
        else
          cout << "Invalid input. Try again: " << endl;
      }
      cout << endl;

      cout << "Columns: ";
      while(true){
        cin >> colInput;
        if(isNumber(colInput)){
          cols = stoi(colInput);
          break;
        }
        else
          cout << "Invalid input. Try again: " << endl;
      }
      cout << endl;


      cout << "Enter the cell density as a float: ";
      while(true){
        cin >> densityInput;
        try{
          density = stof(densityInput);
          break;
        }catch(exception& e){
          cout << "Invalid input. Try again: " << endl;
        }
      }
      cout << endl;

    }
    else if(typeInput == "f"){
      genType = "f";
      cout << "Enter the name of the text file: ";
      while(true){
        cin >> fileInput;
        cout << endl;
        ifstream test(fileInput);;
        if(test.is_open()){
          test.close();
          break;
        }
        else
          cout << "File not found. Try again: " << endl;
      }
      filename = fileInput;
    }else{
      cout << "Invalid input. Try again: " << endl;
    }
  }while(typeInput != "r" && typeInput != "f");

  cout << "Which mode would you like to play in? Enter 'c' for classic, 'd' for donut, or 'm' for mirror: " << endl;
  while(true){
    cin >> modeInput;
    toLower(modeInput);
    if(modeInput == "c" || modeInput == "d" || modeInput == "m"){
      mode = modeInput;
      break;
    }else
      cout << "Invalid mode. Try again: " << endl;
  }

  if(mode == "c" && genType == "r"){
    // grid = new ClassicGrid(rows, cols, density);
    // gridCopy = new ClassicGrid(rows, cols, density);
  }
  else if(mode == "c" && genType == "f"){
    // grid = new ClassicGrid(filename);
    // gridCopy = new ClassicGrid(filename);
  }
  else if(mode == "d" && genType == "r"){
    grid = new DonutGrid(rows, cols, density);
    gridCopy = new DonutGrid(rows, cols, density);
  }
  else if(mode == "d" && genType == "f"){
    grid = new DonutGrid(filename);
    gridCopy = new DonutGrid(filename);
  }
  else if(mode == "m" && genType == "r"){
    // grid = new MirrorGrid(rows, cols, density);
    // gridCopy = new MirrorGrid(rows, cols, density);
  }
  else if(mode == "m" && genType == "f"){
    // grid = new MirrorGrid(filename);
    // gridCopy = new MirrorGrid(filename);
  }

  cout << "Would you like the game to output to the console or a file?" << endl;
  cout << "Type 'c' for console and 'f' for file output: " << endl;
  while(true){
    cin >> gameOutput;
    toLower(gameOutput);
    if(gameOutput == "c"){
      cout << "Would you like to manually control when each generation occurs, or let it run automatically?" << endl;
      cout << "Type 'm' for manual control or 'a' for automatic: " << endl;
      while(true){
        cin >> gameControl;
        toLower(gameControl);
        if(gameControl == "a"){
          automatic = true;
          break;
        }
        else if(gameControl == "m"){
          manual = true;
          break;
        }
        else
          cout << "Invalid input. Try again: " << endl;
      }
      break;
    }
    else if(gameOutput == "f"){
      cout << "Enter the name of the file to be outputted to (.txt extension will be automatically applied): " << endl;
      cin >> fileInput;
      oFS.open(fileInput + ".txt");
      toFile = true;
      break;
    }
    else
      cout << "Invalid input. Try again: " << endl;
  }

}

void Simulation::update(){
  for(int i = 0; i < grid->rows; ++i){
    for(int j = 0; j < grid->cols; ++j){
      if(grid->countNeighbors(i, j) <= 1){
        gridCopy->myGrid[i][j] = '-';
      }
      else if(grid->countNeighbors(i, j) == 3){
        gridCopy->myGrid[i][j] = 'X';
      }
      else if(grid->countNeighbors(i, j) >= 4){
        gridCopy->myGrid[i][j] = '-';
      }
    }
  }
  checkStable();
  for(int i = 0; i < grid->rows; ++i){
    for(int j = 0; j < grid->cols; ++j){
      grid->myGrid[i][j] = gridCopy->myGrid[i][j];
    }
  }
  grid->updateFlatGrid();
}

bool Simulation::checkStable(){
  if(stable > 5)
    return true;
  else{
    if(grid->equals(gridCopy))
      stable++;
    return false;
  }
}

bool Simulation::isNumber(string s){
  for(int i = 0; i < s.length(); ++i){
    if(!isdigit(s[i]))
      return false;
  }
  return true;
}

void Simulation::toLower(string& s){
  for(int i = 0; i < s.length(); ++i)
    s[i] = tolower(s[i]);
}

void Simulation::pause(){
  for(int i = 0; i < 1000; ++i){
    for(int j = 0; j < 1000; ++j){
      for(int k = 0; k < 1000; ++k){

      }
    }
  }
}
