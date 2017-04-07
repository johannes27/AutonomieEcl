#include "game2048.h"
#include <random>
#include <iostream>
using namespace std;
#include <cstdlib>
#include <stdlib.h>
#include <time.h>


Game2048::Game2048()  {

  //init(dim);
}

Game2048::~Game2048()
{
}

// GET AND SET METHODS TO ACCESS PRIVATE ATTRIBUTES :

int Game2048::getField(int x, int y) {
    return field[x][y];
}

void Game2048::setField(int x, int y, int value) {
    field[x][y] = value;
}

int Game2048::getCounterPossibleMoves() {
    return counterPossibleMoves;
}
void Game2048::setCounterPossibleMoves(int a) {
    counterPossibleMoves = a;
}
int Game2048::getDimension(){
    return dim;
}

void Game2048::setDimension(int d) {
    dim = d;
}

// initialize game :

void Game2048::init(int dim)  {
    cout<<"INIT!!"<<endl;
    cout<<"Dimension choosen :"<<dim<<endl;



    // set dimension of matrix with parameter dim :
    field.resize(dim, vector<int>(dim, 0));
    filled.resize(dim, vector<bool>(dim));

    // fill fields with 0 and bool played false :
    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            field[i][j] = 0;
            filled[i][j] = false;
        }
    }

    // fill randomly two fields with 2 :
    srand ( time(NULL) ); // important to not have the same numbers each time
    int x=0,y=0,u=0,v=0;
    while (x==u && y == v) {
        x = rand()%(dim);
        y = rand()%(dim);
        u = rand()%(dim);
        v = rand()%(dim);
    }


    field[x][y] = 2;
    filled[x][y] = true;
    field[u][v] = 2;
    filled[u][v] = true;
    cout<<"printMatrix :"<<endl;
    printField();
}

// reinitialize the game when new game is played :
void Game2048::reinit() {
    cout<<"REINIT!!"<<endl;
    field.resize(dim, vector<int>(dim, 0));
    filled.resize(dim, vector<bool>(dim));

    for (int i=0;i<dim;i++) {
        for (int j=0;j<dim;j++) {
            field[i][j] = 0;
            filled[i][j] = false;

        }
    }
    int x=0,y=0,u=0,v=0;
    while (x==u && y == v) {
    x = rand()%(dim);
    y = rand()%(dim);
    u = rand()%(dim);
    v = rand()%(dim);
    }

    field[x][y] = 2;
    filled[x][y] = true;
    field[u][v] = 2;
    filled[u][v] = true;
    printField();
}

// print out the matrix to test if it works :
void Game2048::printField()  {

    for (int i=0;i<dim;i++) {
        for (int j=0;j<dim;j++) {
            cout<<field[i][j]<<" ";
        }
        cout<<endl;
    }
}

// return points of player (= sum of all fields) :
int Game2048::getPoints() {
    int points = 0;
    for (int i=0;i<dim;i++) {
        for (int j=0;j<dim;j++) {
            if(field[i][j]!=2) points += field[i][j];
        }
    }
    cout<<"points :"<<points<<endl;
    return points;
}

// -----MOVES RIGHT LEFT UP DOWN :-----//
// same principle each time : 3 for loops whereas the third watches
// out for the neighbor fields.
// 3 cases possible :
// @first if statement: move possible, but no combining of 2 numbers
// @second if statement: move possible AND combining of 2 numbers
// @else statement : then move is not possible
// I tried to put all 4 functions in one but didn't succeed
// return false if no moves are possible (important to check gameover)
bool Game2048::moveRight() {

    for(int i=0;i<dim;i++) {
        for(int j=dim-2;j>=0;j--) {
            for(int h=0;h<dim-1-j;h++) {
                if(field[i][j+h] != 0 && field[i][j+1+h] == 0 && j+1+h < dim) {
                    field[i][j+1+h] = field[i][j+h];
                    field[i][j+h] = 0;
                    cout<<"STEP RIGHT"<<endl;
                    counterPossibleMoves +=1;
               }
                else if (field[i][j+h] != 0 && field[i][j+1+h] == field[i][j+h] && j+1+h < dim){
                    field[i][j+1+h] = field[i][j+h] + field[i][j+h+1];
                    field[i][j+h] = 0;
                    counterPossibleMoves +=1;
                    break;
                }
            else {
                    cout<<"Move not possible"<<endl;
            }
            }
        }

        }
   updateFilled();
   if(counterPossibleMoves==0) return false;
   return true;
}

bool Game2048::moveLeft() {

    for(int i=0;i<dim;i++) {
        for(int j=1;j<dim;j++) {
            for(int h=0;h<j;h++) {
                if(field[i][j-h]!= 0 && field[i][j-1-h] == 0 && j-1-h >= 0) {
                    field[i][j-1-h] = field[i][j-h];
                    field[i][j-h] = 0;
                    cout<<"STEP"<<endl;
                    counterPossibleMoves +=1;
                }
                else if (field[i][j-h] != 0 && field[i][j-1-h] == field[i][j-h] && j-1-h >=0){
                    field[i][j-1-h] = field[i][j-h] + field[i][j-h-1];
                    field[i][j-h] = 0;
                    counterPossibleMoves +=1;
                    break;
                }
                else {
                    cout<<"Move not possible"<<endl;
            }
            }
        }
        }
    updateFilled();
    if(counterPossibleMoves==0) return false;
    return true;

}

bool Game2048::moveUp() {


    for(int i=1;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            for(int h=0;h<i;h++) {
                if(field[i-h][j] != 0 && field[i-1-h][j] == 0 && i-h-1 >= 0) {
                    field[i-1-h][j] = field[i-h][j];
                    field[i-h][j] = 0;
                    cout<<"STEP"<<endl;
                    counterPossibleMoves +=1;
                }
                else if (field[i-h][j] != 0 && field[i-h-1][j] == field[i-h][j] && i-h-1 >= 0){
                    field[i-h-1][j] = field[i-h][j] + field[i-h-1][j];
                    field[i-h][j] = 0;
                    counterPossibleMoves +=1;
                    break;
                }
                else {
                    cout<<"Move not possible"<<endl;
                }
            }
        }
        }
    updateFilled();
    if(counterPossibleMoves==0) return false;
    return true;
}

bool Game2048::moveDown() {

    for(int i=dim-2;i>=0;i--) {
        for(int j=0;j<dim;j++) {
            for(int h=0;h<dim-i-1;h++) {
                if(field[i+h][j] != 0 && field[i+1+h][j] == 0 && i+1+h < dim) {
                    field[i+1+h][j] = field[i+h][j];
                    field[i+h][j] = 0;
                    cout<<"STEP"<<endl;
                    counterPossibleMoves +=1;
                }
                else if (field[i+h][j] != 0 && field[i+1+h][j] == field[i+h][j] && i+1+h < dim){
                    field[i+h+1][j] = field[i+h][j] + field[i+h+1][j];
                    field[i+h][j] = 0;                    
                    counterPossibleMoves +=1;
                    break;
                }
                else {
                    cout<<"Move not possible"<<endl;
            }
            }
        }
        }
    updateFilled();
    if(counterPossibleMoves==0) return false;
    return true;
}

// bool field has to be updated after each move :
void Game2048::updateFilled() {

    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            if (field[i][j] != 0) {
                filled[i][j] = true;
            }
            else {
                filled[i][j] = false;
            }
}
    }
}

// add number 2 or 4 to the field (66,6% vs 33,3%) :
void Game2048::addNumber() {
    cout<<"Game2048::addNumber() executed"<<endl;

    int x = rand()%dim;
    int y = rand()%dim;
    static const int values[3] = {2,2,4};

    if (field[x][y] == 0) {
        field[x][y] = values[rand()%3];
        filled[x][y] = true;
    }
    else {
        addNumber();
    }
}

// after each move check if game is over or not
bool Game2048::checkForGameOver() {

    int counter = 0;
    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            if(field[i][j] != 0) counter+=1;
        }
    }
    cout<<"counter of empty fields ="<<counter<<endl;
    if (counter >= dim*dim) {
          if (moveRight()==false && moveLeft()==false && moveUp()==false && moveDown() == false) {
            cout<<"GAMEOVER"<<endl;
            return true;
        }
    }
    return false;
}




