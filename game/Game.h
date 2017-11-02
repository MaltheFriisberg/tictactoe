//
// Created by malthe on 10/12/17.
//

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H

const char human = 'X';
const char ai = 'O';
const int MAX = 1000;
const int MIN = -1000;


enum Player { HUMAN, AI };

struct Move{
    int x;
    int y;
};

class Game {


private:
    char gameBoard[9];

    int AInextMove;

    void printBoard();

    bool gameOver();

    bool checkWin(Player player);

    void getHumanMove();

    int score();

    int minimax(bool minimizingForPlayer);


public:
    //constructor
    Game();
    //game driver
    void play();

};


#endif //TICTACTOE_GAME_H
