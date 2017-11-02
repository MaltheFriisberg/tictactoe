//
// Created by malthe on 10/12/17.
//

#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H

const char human = 'X';
const char ai = 'O';

enum Player { HUMAN, AI };

struct Move{
    int x;
    int y;
};

class Game {


private:
    char gameBoard[3][3];

    void printBoard();

    bool gameOver();

    bool checkWin(Player player);

    void getHumanMove();

    int score();

    Move minimax(char AIBoard[3][3]);

    int minSearch(char AIBoard[3][3]);

    int maxSearch(char AIBoard[3][3]);

public:
    //constructor
    Game();

    void play();

};


#endif //TICTACTOE_GAME_H
