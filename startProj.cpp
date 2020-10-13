#include<iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;
//This class is meant to prompt the user and create the appropriate grid
class Intro {
    float den;
    int dimy;
    int dimx;
    fstream inputfile;
    int file_row;
    int file_col;
    string fileName;
    char letter;


    public:
//This method welcomes the user to the game and collects input for right method of game
     void begin(){

       bool f = true;
       while(f){
          std::cout << "--------------WELCOME TO THE GAME OF LIFE--------------" << '\n';
          std::cout << '\n';
           cout << "If you would you like to rovide a map file of the world press 'F'" << '\n';
           std::cout << "if you would like a random assignment press 'R'" << '\n';

           std::cout << "r(random)   ,   f(map file): ";
           cin >> letter;
//Random mode
             if (letter == 'R' || letter == 'r') {
             cout << "Please enter a value greater than 0 and less than or equal to 1 representing the initial population density of the world: " <<endl;
             float density;
             cout << "Density = ";
             cin >> density;
             den = density;

             cout << "Great now enter the desired dimention of the world(grid). X axis fallowed by Y axis" <<endl;
             int xdim;
             int ydim;
             cout << "Horizantal = ";
             cin >> xdim;
             dimx = xdim;

             cout << "Vertical = ";
             cin >> ydim;
             dimy = ydim;
             f = false;


           }
//File input mode
            else if(letter == 'F' || letter == 'f'){
              cout << "Please enter name of file (include .txt at the end)" << endl;
              cin >> fileName;
              break;
            }
             else {
               std::cout << "You have entered an invalid input try agian. " << '\n';
             }
        }


    }
//The appropriate getters
    char getletter(){
      return letter;
    }

    int getx(){
      return dimx;
    }

    int gety(){
      return dimy;
    }

    float getden(){
      return den;
    }

    string getFileName() {
      return fileName;
    }
    int get_file_row() {
      return file_row;
    }
    int get_file_col() {
      return file_col;
    }


//This method populates the grid based on the user input for the random method
void populate(char** arr, double aaa, int row, int col){
//putting the 'X' in random positions throughout the grid
    for(int b = 0; b < aaa; b++){
    random_device seeder;
    mt19937 engine(seeder());
    uniform_int_distribution<int> dist(0, col-1);
    uniform_int_distribution<int> disty(0, row-1);

    int u = dist(engine);
    int f = disty(engine);

    if(arr[u][f] == 'X'){
      bool kill= false;
      for(int d =0; d < row; ++d){
        if(kill){
          break;
        }
        for (int c = 0; c < col; ++c) {
          if(arr[c][d] == '-'){
            arr[c][d] = 'X';
            kill = true;
            break;
          }
        }
      }
    }

    arr[u][f] = 'X';
    }
  }
//Reads map from a file text and collects its dimensions
  char** readFileBoard(string filename) {
    inputfile.open(filename);
    cout << "Opening Grid......" << endl;
    int row, col;
    if(inputfile.is_open()) {
      inputfile >> row;
      inputfile >> col;
      file_row = row;
      file_col = col;
      cout << row << " " << col << endl;
      char** arr = new char*[row];
      for(int i = 0; i < row; ++i) {
        arr[i] = new char[col];
        for(int j = 0; j < col; ++j) {
          inputfile >> arr[i][j];
        }
      }
      return arr;
    } else {
      cout << "Unable to open file" << endl;
    }
  }

//Creates grid for the random method with correct X and Y axis
  char** makegrid(int x, int y) {

    char** arr = new char*[y];

    for(int i =0; i < y; ++i){
      arr[i] = new char[x];
      for(int j =0; j<x; ++j){

          arr[i][j] = '-';
      }
    }
    return arr;
  }
//Method for capturing desired gamemode of user
  char getGameMode(){
    char input;
    std::cout  << '\n';
    std::cout << "    For Classic: c " << '\n';
    std::cout << "    For Donut: d " << '\n';
    std::cout << "    For Mirror: m " << '\n';
    std::cout << "Please enter desired mode: ";
    cin >> input;
    if(input == 'c' || input == 'C'){
    return 'c';
    }
    else if(input == 'd' || input == 'D'){
    return 'd';
    }
    else if(input == 'm' || input == 'M'){
    return 'm';
    }

    std::cout << "You have entered an inccorect inout running defult classic mode....." << '\n';
    return 'c';
  }

};
