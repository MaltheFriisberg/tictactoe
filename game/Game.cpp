//
// Created by malthe on 10/12/17.
//

#include <array>
#include <iostream>
#include <iomanip>
#include "Game.h"

using namespace std;



Game::Game() {

    for(int i = 0; i < 9; i++) {
        gameBoard[i] = '-';
    }

}

void Game::printBoard() {
    cout << "-------------------"<< '\n';
    for(int i = 0; i < 9; i++) {
        cout  << "|";
        char result = gameBoard[i];
        cout << setw(3) << gameBoard[i] << setw(3) << " |";
        if(i==2 || i==5) {
            cout << '\n';
        }

    }
    cout << '\n' << "-------------------" << '\n';

}

void Game::play() {

    int turn = 0;
    printBoard();
    while(!checkWin(HUMAN) && !checkWin(AI) && !gameOver()) {
        // human move
        if(turn % 2 == 0) {
            getHumanMove();
            if(checkWin(HUMAN)) cout << "Human Player Wins" << endl;
            turn++;
            printBoard();
        } else {
            cout << endl << "Computer Player Move:" << endl;
            minimax(true);
            //Move AImove1 = evaluateMove(AImove);
            int test = AInextMove;
            gameBoard[AInextMove] = ai;
            if(checkWin(AI)) cout << "Computer Player Wins" << endl;
            turn++;
            printBoard();
        }
    }

}

void Game::getHumanMove() {
    cout << "enter move : ";
    int c;
    cin >> c;
    string restofline;
    getline(cin, restofline); // get garbage chars after move
    gameBoard[c-1] = human;

}


int Game::minimax(bool minimizingForPlayer)// The minimax function
{
    //initial values min and max
    int max_val=-1000,min_val=1000;
    int i,j,value = 1;
    //base cases
    if(checkWin(AI))
    {return 10;}
    else if(checkWin(HUMAN))
    {return -10;}
    else if(gameOver())
    {return 0;}
    //end base cases

    //Score of the move
    int score[9] = {1,1,1,1,1,1,1,1,1};

    //check all possible moves
    for(i=0;i<9;i++)
    {
        if(gameBoard[i] == '-')
        {
            if(min_val>max_val) // pruning (reversed) no need to go deeper
            {
                if(minimizingForPlayer == true)
                {
                    gameBoard[i] = ai;
                    //Maximize for CPU
                    value = minimax(false);
                }
                else
                {
                    gameBoard[i] = human;
                    //Minimize for player
                    value = minimax(true);
                }
                gameBoard[i] = '-';
                score[i] = value;
            }
        }
    }

    if(minimizingForPlayer == true)
    {
        max_val = -1000;
        for(j=0;j<9;j++)
        {
            if(score[j] > max_val && score[j] != 1)
            {
                max_val = score[j];
                AInextMove = j;
            }
        }
        return max_val;
    }
    if(minimizingForPlayer == false)
    {
        min_val = 1000;
        for(j=0;j<9;j++)
        {
            if(score[j] < min_val && score[j] != 1)
            {
                min_val = score[j];
                AInextMove = j;
            }
        }
        return min_val;
    }
}

int Game::score() {
    if(checkWin(HUMAN)) { return 10; }
    else if(checkWin(AI)) { return -10; }
    return 0; // draw
}

bool Game::checkWin(Player player) {

    char playerChar;
    if(player == HUMAN) {
        playerChar = human;
    } else{
        playerChar = ai;
    }

    for(int i=0;i<9;i+=3)
    {
        if((gameBoard[i]==gameBoard[i+1])&&(gameBoard[i+1]==gameBoard[i+2])&&(gameBoard[i]==playerChar))
            return true;
    }
    for(int i=0;i<3;i++)
    {
        if((gameBoard[i]==gameBoard[i+3])&&(gameBoard[i+3]==gameBoard[i+6])&&(gameBoard[i]==playerChar))
            return true;
    }
    if((gameBoard[0]==gameBoard[4])&&(gameBoard[4]==gameBoard[8])&&(gameBoard[0]==playerChar))
    {
        return true;
    }
    if((gameBoard[2]==gameBoard[4])&&(gameBoard[4]==gameBoard[6])&&(gameBoard[2]==playerChar))
    {
        return true;
    }
    return false;
}

bool Game::gameOver() {
    for(int i =0;i<9;i++)
    {
        if(gameBoard[i]!=ai)
        {
            if(gameBoard[i]!=human)
            {
                return false;
            }
        }
    }
    return true;
}
