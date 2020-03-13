#include "Simulation.h"

//The default constructor initialized key values to their respective zeroes
Simulation::Simulation(){
  stable = 0;
  manual = false;
  automatic = false;
  toFile = false;
}
//The simulation's grid destructors are called and the output filestream is closed
Simulation::~Simulation(){
  delete grid;
  delete gridCopy;
  oFS.close();
}

//The start method initializes the simulation by gathering info from the user
void Simulation::start(){
  //these variables will act as storage for all the different types of input gathered
  string typeInput = "";
  string modeInput = "";
  string fileInput = "";
  string colInput = "";
  string rowInput = "";
  string densityInput = "";
  string gameControl = "";
  string gameOutput = "";

  cout << "Welcome to the Game of Life. Type 'r' for a random map or 'f' for a map file input: " << endl;
  //This initial loop will execute code depending on if the user chooses random or file input for the map
  do{
    cin >> typeInput;
    toLower(typeInput);
    //This block will activate if the user selects random
    if(typeInput == "r"){
      genType = "r";
      cout << "Enter the dimensions for your grid below: " << endl;
      //The size of the rows is taken and converted to an integer and stored in rows
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

      //The size of the columns is taken and converted to an integer and stored in cols
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

      //The density value is read in and converted to a float and stored in density
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
    //This block will activate if the user chose to input a file
    else if(typeInput == "f"){
      genType = "f";
      cout << "Enter the name of the text file: ";
      while(true){
        cin >> fileInput;
        cout << endl;
        ifstream test(fileInput);;
        //This checks if the file exists or not by attempting to open it
        if(test.is_open()){
          test.close();
          break;
        }
        else
          cout << "File not found. Try again: " << endl;
      }
      //The filename is stored for later use
      filename = fileInput;
    }else{
      cout << "Invalid input. Try again: " << endl;
    }
  }while(typeInput != "r" && typeInput != "f");

  cout << "Which mode would you like to play in? Enter 'c' for classic, 'd' for donut, or 'm' for mirror: " << endl;
  //This loop will retrieve the mode data from the user
  while(true){
    cin >> modeInput;
    toLower(modeInput);
    if(modeInput == "c" || modeInput == "d" || modeInput == "m"){
      mode = modeInput;
      break;
    }else
      cout << "Invalid mode. Try again: " << endl;
  }
  //Each of the conditions below will call different constructors depending on the mode and map type
  if(mode == "c" && genType == "r"){
    grid = new ClassicGrid(rows, cols, density);
    gridCopy = new ClassicGrid(rows, cols, density);
  }
  else if(mode == "c" && genType == "f"){
    grid = new ClassicGrid(filename);
    gridCopy = new ClassicGrid(filename);
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
    grid = new MirrorGrid(rows, cols, density);
    gridCopy = new MirrorGrid(rows, cols, density);
  }
  else if(mode == "m" && genType == "f"){
    grid = new MirrorGrid(filename);
    gridCopy = new MirrorGrid(filename);
  }

  cout << "Would you like the game to output to the console or a file?" << endl;
  cout << "Type 'c' for console and 'f' for file output: " << endl;
  //This loop will check which output style the user wants
  while(true){
    cin >> gameOutput;
    toLower(gameOutput);
    //If it is console, they will then be asked if they want manual or automatic control
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
    //If the user selects file output, an ofstream will be created to that file
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

//The update method is called to simulate each generation. 1 call represents 1 generation.
void Simulation::update(){
  //This nested for loop iterates through the simulation's grid
  for(int i = 0; i < grid->rows; ++i){
    for(int j = 0; j < grid->cols; ++j){
      //These if-else statements represent the different conditions for varying neighbor counts
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
  //This function is called to check if the board is the same as the last generation
  checkStable();
  //The main grid has the gridcopy's values stored in it all at once
  for(int i = 0; i < grid->rows; ++i){
    for(int j = 0; j < grid->cols; ++j){
      grid->myGrid[i][j] = gridCopy->myGrid[i][j];
    }
  }
  //As the new grid has changed, the flat grid is updated to match it
  grid->updateFlatGrid();
}

//This function accesses the stable variable to see if it has gone over its limit of 5
bool Simulation::checkStable(){
  if(stable > 5)
    return true;
  //If stable isn't over 5, then it will check to see if the grid and gridcopy are the same
  else{
    if(grid->equals(gridCopy))
      //Stable will be incremented if so
      stable++;
    return false;
  }
}

//This is a simple method to see if a string is a numeric value
bool Simulation::isNumber(string s){
  for(int i = 0; i < s.length(); ++i){
    if(!isdigit(s[i]))
      return false;
  }
  return true;
}

//This method converts a string to lowercase
void Simulation::toLower(string& s){
  for(int i = 0; i < s.length(); ++i)
    s[i] = tolower(s[i]);
}

//O(n^3) == long runtime == pause
void Simulation::pause(){
  for(int i = 0; i < 1000; ++i){
    for(int j = 0; j < 1000; ++j){
      for(int k = 0; k < 1000; ++k){

      }
    }
  }
}
