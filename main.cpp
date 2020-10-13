#include<iostream>
#include <cmath>
#include <random>
#include "startProj.cpp"
#include "GameStrt.cpp"
using namespace std;

int main(){
//Making instence of Intro Class made for introduction into game
  Intro b;
  b.begin();
  int row;
  int col;
//Checking which gmae mehod user wants to use
  char **arr;
  if(b.getletter() == 'f' || b.getletter() == 'F'){
    arr = b.readFileBoard(b.getFileName());
    row = b.get_file_row();
    col = b.get_file_col();
  }
  else if(b.getletter() == 'r' || b.getletter() == 'R'){

  col = b.getx();
  row = b.gety();
  float den = b.getden();
  arr = b.makegrid(row, col);
  double aaa;
  aaa = round(den*row*col);
  b.populate(arr, aaa, row, col);

 }
//Making an instence of GameStrt(grid)
 GameStrt d = GameStrt(arr, col, row);
//Grabs the desired game mode
 char mode = b.getGameMode();
//Starts Game
 d.startGame(mode);


return 0;
}
