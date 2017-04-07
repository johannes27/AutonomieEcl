#include "spider.h"
#include "stdio.h"
#include <iostream>
using namespace std;

Spider::Spider()
{
    currentPlayer = 1; //start with player 1
}

// GET AND SET FUNCTIONS TO ACCESS PRIVATE VARIABLES :

int Spider::getWinner() {
    return winner;
}

void Spider::setWinner(int a) {
    winner = a;
}

int Spider::getCurrentPlayer() {
    return currentPlayer;
}

void Spider::setCurrentPlayer(int a) {
    currentPlayer = a;
}

int Spider::getField(int a) {
    return board[a-1];
}

void Spider::setField(int a, int b ) {
    board[a-1] = b;
}

void Spider::setFieldPlayed(int a, bool b) {
    fieldPlayed[a-1] = b;
}

int Spider::getWinsOfPlayer(int a) {
    return winsPlayer[a-1];
}

void Spider::resetWinsOfPlayer() {
    winsPlayer[0] = 0;
    winsPlayer[1] = 0;
}

void Spider::setGameFinished(bool a) {
    gameFinished = a;
}

// fill field with number 1 or 2 (for player 1 or 2)
// variable currentPlayer allows to know if to fill with 1 or 2
// @param : field which has to be filled / was played
void Spider::fillBoard(int field) {

    switch(currentPlayer) {
        case 1 : board[field-1]=1; fieldPlayed[field-1] = true;  break;
        case 2 : board[field-1]=2; fieldPlayed[field-1] = true;  break;
        default : cout<<"Invalid move"<<endl; break;
    };
}

// after each move current player has to be switched :
void Spider::switchPlayer() {
    switch(getCurrentPlayer()) {
        case 1 : setCurrentPlayer(2); break;
        case 2 : setCurrentPlayer(1); break;
        default : cout<<"Invalid switch"<<endl; break;
    };
}

// do a move : fill bord in case field hasn't been played already
void Spider::move(int playersFieldChoice) {

    if (fieldPlayed[playersFieldChoice-1] == false) {
        fillBoard(playersFieldChoice);
    }
    else {
        cout<<"Move not possible, field already played!"<<endl;
    }
}

/*
 * Method checks if the game has finished and if there's a winner
 * @return -1 : game is in progress
 * @return 0 : game finished and no winner = Draw
 * @return 1 : game finished and winner
 */
int Spider::checkWin() {

    int stepsPlayed = 0;
    for (int i=0;i<9;i++) {
        if(fieldPlayed[i]== true) stepsPlayed += 1;
    }

    if(board[0]==board[1] && board[1]==board[2]&& board[0]!=0) {
        endGame();
        return 1;
    }
    else if (board[3]==board[4] && board[4]==board[5] && board[3]!=0) {
        endGame();
        return 1;
    }
    else if (board[6]==board[7] && board[7]==board[8] && board[6]!=0) {
        endGame();
        return 1;
    }
    else if (board[0]==board[3] && board[3]==board[6] && board[0]!=0) {
        endGame();
        return 1;
    }
    else if (board[1]==board[4] && board[4]==board[7] && board[1]!=0) {
        endGame();
        return 1;
    }
    else if (board[2]==board[5] && board[5]==board[8] && board[2]!=0) {
        endGame();
        return 1;
    }
    else if (board[0]==board[4] && board[4]==board[8] && board[0]!=0) {
        endGame();
        return 1;
    }
    else if (board[2]==board[4] && board[4]==board[6] && board[2]!=0) {
        endGame();
        return 1;
    }
    else if (stepsPlayed==9 && gameFinished==false) {
        cout<<"DRAW!"<<stepsPlayed<<endl;
        return 0;
    }
    else {
        cout<<stepsPlayed<<endl;
        cout<<"gameFinished?"<<gameFinished<<endl;
        return -1;
    }
}

// function is called when game is finished
// winner is determined
void Spider::endGame() {
    setWinner(getCurrentPlayer());
    gameFinished = true;
    winsPlayer[getWinner()-1] += 1;
}

// print out winner to test if it works :
void Spider::printWinner() {
    if(checkWin() == 1) {
        cout<<"The winner is:"<<getWinner()<<endl;
    }
    else {
        cout<<"There is no winner!";
    }
}

// print out board to test if it works :
void Spider::printBoard() {
    for(int i=0;i<9;i++) {
        cout<<"board"<<i<<":"<<board[i]<<"  bool Played:"<<fieldPlayed[i]<<endl;
    }
    cout<<endl;
}
