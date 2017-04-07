#ifndef SPIDER_H
#define SPIDER_H



class Spider
{
public:
    Spider();
    int getWinner();
    void setWinner(int);
    int getCurrentPlayer();
    void setCurrentPlayer(int);
    int getField(int);
    void setField(int,int);
    void setFieldPlayed(int,bool);
    int getWinsOfPlayer(int);
    void resetWinsOfPlayer();
    void setGameFinished(bool);
    void move(int);
    void fillBoard(int);
    void switchPlayer();
    void endGame();
    void printBoard();
    int checkWin();
    void printWinner();


private:
    int board[9] = {0,0,0,0,0,0,0,0,0};
    int winsPlayer[2]= {0,0};
    int winner = 0;
    int currentPlayer = 0;
    bool fieldPlayed[9] = {false,false,false,false,false,false,false,false,false};
    bool gameFinished = false;






};

#endif // SPIDER_H
