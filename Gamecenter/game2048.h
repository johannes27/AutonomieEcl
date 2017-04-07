#ifndef GAME2048_H
#define GAME2048_H
#include <vector>
using namespace std;


class Game2048
{
public:
    Game2048();
    ~Game2048();
    int getField(int,int);
    void setField(int,int,int);
    int getCounterPossibleMoves();
    void setCounterPossibleMoves(int);
    int getDimension();
    void setDimension(int d);
    void init(int dim);
    void reinit();
    void printField();
    int getPoints();
    bool moveRight();
    bool moveLeft();
    bool moveUp();
    bool moveDown();
    void addNumber();
    void updateFilled();
    bool checkForGameOver();



private:

    int N = 5;
    vector< vector<int> > field;
    vector< vector<bool> > filled;
    int score = 0;
    int counterPossibleMoves;
    bool foundPair;
    int dim = 5;
};



#endif // GAME2048_H
