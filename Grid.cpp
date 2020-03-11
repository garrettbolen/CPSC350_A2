#include "Grid.h"

Grid::Grid(int r, int c, float density){
  srand(time(NULL));
  rows = r;
  cols = c;
  popDensity = density;

  int size = rows * cols;
  int numCells = popDensity * size;
  init(rows, cols);

  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      myGrid[i][j] = '-';

  for(int i = 0; i < numCells; ++i){
    int num1 = rand() % rows;
    int num2 = rand() % cols;
    if(myGrid[num1][num2] == 'X')
      i--;
    else
      myGrid[num1][num2] = 'X';
  }
}

Grid::Grid(string filename){
  ifstream inFS;
  inFS.open(filename);

  string line = "";

  getline(inFS, line);
  rows = stoi(line);

  getline(inFS, line);
  cols = stoi(line);

  init(rows, cols);

  flatGrid = new char[rows*cols];
  int idx = 0;

  /*The goal of this nested for loop is to read in chars from the file into both
  the normal and flat grids*/
  for(int i = 0; i < rows; ++i){
    getline(inFS, line);
    for(int j = 0; j < cols; ++j){
      myGrid[i][j] = line[j];
      flatGrid[idx] = line[j];
      idx++;
    }
  }
}

Grid::~Grid(){
  for(int i = 0; i < rows; ++i){
    delete [] myGrid[i];
  }
  delete [] myGrid;
  delete [] flatGrid;
}

void Grid::init(int r, int c){
  rows = r;
  cols = c;

  myGrid = new char*[rows];
  for(int i = 0; i < rows; ++i){
    myGrid[i] = new char[cols];
  }
}

void Grid::print(){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      cout << myGrid[i][j];
    }
    cout << endl;
  }
}

//A simple formula that converts a 2D index to a "flat" index in one dimension
int Grid::flatIndex(int i, int j){
  return cols * i + j;
}

void Grid::updateFlatGrid(){
  int idx = 0;
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      flatGrid[idx] = myGrid[i][j];
      idx++;
    }
  }
}
