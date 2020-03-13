#include "Grid.h"

//This constructor takes in the number of rows, columns, and population density as parameters
Grid::Grid(int r, int c, float density){
  //srand is seeded with time for later use
  srand(time(NULL));

  //The arguments passed are stored in their respective member variables
  rows = r;
  cols = c;
  popDensity = density;

  //Size and the number of cells in the grid are calculated
  int size = rows * cols;
  int numCells = popDensity * size;

  //The grid is initialized with the specified rows and columns
  init(rows, cols);

  //Initially, it is filled in with blanks
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      myGrid[i][j] = '-';

  //This loop iterates over the number of cells to be added to the grid
  for(int i = 0; i < numCells; ++i){
    //Each time, new random indexes are generated for where the cells will be placed
    int num1 = rand() % rows;
    int num2 = rand() % cols;
    //If there is already a cell there, the loop will simply restart that iteration to generate a new one
    if(myGrid[num1][num2] == 'X')
      i--;
    //Otherwise the cell is placed in the new random location
    else
      myGrid[num1][num2] = 'X';
  }
  //Once the grid is filled out, its flat version is updated accordingly
  updateFlatGrid();
}

//This constructor takes in a filename as a parameter
Grid::Grid(string filename){
  //A filestream is opened to read in the information from the users file
  ifstream inFS;
  inFS.open(filename);

  string line = "";
  //The rows and columns are grabbed from the first two lines of the file
  getline(inFS, line);
  rows = stoi(line);

  getline(inFS, line);
  cols = stoi(line);

  //The grid is initialized accordingly
  init(rows, cols);

  //The goal of this nested for loop is to read in chars from the file into the grid
  for(int i = 0; i < rows; ++i){
    getline(inFS, line);
    for(int j = 0; j < cols; ++j)
      myGrid[i][j] = line[j];
  }
  //The flat grid is updated once the 2D grid is filled out
  updateFlatGrid();
}

Grid::~Grid(){
  //All new arrays created are destroyed
  for(int i = 0; i < rows; ++i){
    delete [] myGrid[i];
  }
  delete [] myGrid;
  delete [] flatGrid;
}

//This method creates the grid and flatgrid using inputed row and column sizes
void Grid::init(int r, int c){
  rows = r;
  cols = c;
  flatGrid = new char[rows*cols];

  myGrid = new char*[rows];
  for(int i = 0; i < rows; ++i){
    myGrid[i] = new char[cols];
  }
}

//This function loops through the grid and prints each index out in the console
void Grid::print(){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      cout << myGrid[i][j];
    }
    cout << endl;
  }
}

//This function will loop through the grid and print it to a file
void Grid::print(ofstream& oFS){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      oFS << myGrid[i][j];
    }
    oFS << endl;
  }
}

//A simple formula that converts a 2D index to a "flat" index in one dimension
int Grid::flatIndex(int i, int j){
  return cols * i + j;
}

//Scans the 2D grid and updates the flat version to mirror it
void Grid::updateFlatGrid(){
  int idx = 0;
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      flatGrid[idx] = myGrid[i][j];
      idx++;
    }
  }
}

//Checks if two grids are equal
bool Grid::equals(Grid* grid){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      if(myGrid[i][j] != grid->myGrid[i][j])
        return false;
    }
  }
  return true;
}
