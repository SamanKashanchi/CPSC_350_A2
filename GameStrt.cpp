#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <random>
using namespace std;
using std::cout;
//This method applies the rules of the game to the already made grid
class GameStrt{

  private:
    int col;
    int row;
    char** arr;

  public:
//Constructor method
    GameStrt(char** _arr, int r, int c){
      arr = _arr;
      row = r;
      col = c;
    }

//Method for printing out grid
    void printArray(){

      for(int i =0; i < row; ++i){
        for(int j =0; j<col; ++j){
          cout << arr[i][j];
        }
        cout << '\n';
      }
    }
//Method that copies the original grid on to the new grid
    void copy_original(char** newArry){
      for(int i =0; i < row; ++i){
        for(int j =0; j<col; ++j){
          newArry[i][j] = arr[i][j];
        }
      }
    }
//Method that copies the new grid on to the original grid
    void copy_new(char** newArry){
      for(int i =0; i < row; ++i){
        for(int j =0; j<col; ++j){
          arr[i][j] = newArry[i][j];
        }
      }
    }
//Metthod to check if population has stabalized (checks if original grid = new grid)
    bool noChange(char** stabalized){

      for(int i =0; i < row; ++i){
        for(int j =0; j<col; ++j){
          if(arr[i][j] != stabalized[i][j]) {

            return false;
          }
        }
      }
      std::cout << "The population has stabalized" << '\n';
      return true;
    }
//Method that checks if anyone is alive
 bool AllDead(){
      for(int i =0; i < row; ++i){
        for(int j =0; j<col; ++j){
          if(arr[i][j] == 'X') {
            return false;
          }
      }
    }
    std::cout << "Every one is dead." << '\n';
    return true;
  }
//Method for donut mode
 int donut(int v, int curr){

     if (v < 0) {
       return curr-1;
     }
     else if (v == curr){
       return 0;
     }
     else return v;
   }

//Method for mirror mode
 int mirror(int v, int curr) {
     if (v < 0) {
       return 0;
     }
     else if(v >= curr) {
       return curr-1;
     }
    else return v;
   }
//Wrapper that checks and assigns the appropriate gamemode
  int modeCheckR(int val, char m) {
    if(m == 'c') return val;
    else if(m == 'd') return donut(val, row);
    else if(m == 'm') return mirror(val, row);
      else return -1;
  }
//Wrapper that checks and assigns the appropriate gamemode
  int modeCheckC(int val, char m) {
    if(m == 'c') return val;
    else if(m == 'd') return donut(val, col);
    else if (m == 'm') return mirror(val, col);
      else return -1;
  }


//Method that populates next generation based on gamemode(The rules of the Game)
    char makeNewGen(int x, int y, char m){
      int neighbor = 0;
      if (modeCheckR(x - 1, m) >= 0 && modeCheckC(y - 1, m) >=0 && arr[modeCheckR(x - 1, m)][modeCheckC(y - 1, m)] == 'X') neighbor++;
      if (modeCheckR(x - 1, m) >= 0 && arr[modeCheckR(x - 1, m)][y] == 'X') neighbor++;
      if (modeCheckR(x - 1, m) >= 0 && modeCheckC(y + 1, m) < col && arr[modeCheckR(x - 1, m)][modeCheckC(y + 1, m)] == 'X') neighbor++;
      if (modeCheckC(y - 1, m) >= 0 && arr[x][(modeCheckC(y - 1, m))] == 'X') neighbor++;
      if (modeCheckC(y + 1, m) < col && arr[x][modeCheckC(y + 1, m)] == 'X') neighbor++;
      if (modeCheckR(x + 1, m) < row && modeCheckC(y - 1, m) >=0 && arr[modeCheckR(x + 1, m)][modeCheckC(y - 1, m)] == 'X') neighbor++;
      if (modeCheckR(x + 1, m) < row && arr[modeCheckR(x + 1, m)][y] == 'X') neighbor++;
      if (modeCheckR(x + 1, m) < row && modeCheckC(y + 1, m) < col && arr[modeCheckR(x + 1, m)][modeCheckC(y + 1, m)] == 'X') neighbor++;

      if(neighbor < 2) return '-';
      else if(neighbor == 2) return arr[x][y];
      else if(neighbor == 3) return 'X';
      else if(neighbor > 3) return '-';
      else return 1;
    }
//Method that applies the logic of the game. Also counts generations.
    void startGame(char gameMode){

      int gen = 0;
      char** newArry = new char*[row];
      for(int i = 0; i < row; ++i){
        newArry[i] = new char[col];
      }
      copy_original(newArry);
      while(true){
        ++gen;
        cout << "Generation: " <<gen<< '\n';
        printArray();
        for(int i =0; i < row; ++i){
          for(int j =0; j<col; ++j){
            newArry[i][j] = makeNewGen(i, j, gameMode);
          }
        }
        if(noChange(newArry)) break;
        copy_new(newArry);
        if(AllDead()) break;
      }
      delete[] newArry;
    }
};
