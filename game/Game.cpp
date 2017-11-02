//
// Created by malthe on 10/12/17.
//

#include <array>
#include <iostream>
#include <iomanip>
#include "Game.h"

using namespace std;

Game::Game() {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            gameBoard[i][j] = '-';
        }
    }

}

void Game::printBoard() {
    cout << "-------------------";
    for(int i = 0; i < 3; i++) {
        cout << '\n' << "|";
        for(int j = 0; j < 3; j++) {
            cout << setw(3) << gameBoard[i][j] << setw(3) << " |";
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
            Move AImove = minimax(gameBoard);
            gameBoard[AImove.x][AImove.y] = ai;
            if(checkWin(AI)) cout << "Computer Player Wins" << endl;
            turn++;
            printBoard();
        }
    }

}

void Game::getHumanMove() {
    int x, y = -1; // arbitrary assignment to init loop
    while(x < 0 || x > 2 || y < 0 || y > 2) {
        // Loop until a valid move is entered
        cout << "Enter your move in coordinate form, ex: (1,3)." << endl;
        cout << "Your Move: ";
        char c;
        string restofline;
        cin >> c >> c;
        x = c - '0' - 1;
        cin >> c >> c;
        y = c - '0' - 1;
        getline(cin, restofline); // get garbage chars after move
    }
    gameBoard[x][y] = human;

}

int Game::maxSearch(char AIboard[3][3]) {
    if(gameOver()) return score();
    Move bestMove;

    int bestMoveScore = -1000;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = human;
                int tempMoveScore = minSearch(AIboard);
                if(tempMoveScore >= bestMoveScore) {
                    bestMoveScore = tempMoveScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '-';
            }
        }
    }

    return bestMoveScore;
}

int Game::minSearch(char AIboard[3][3]) {
    if(gameOver()) return score();
    Move bestMove;

    int bestMoveScore = 1000;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = ai;
                int tempMove = maxSearch(AIboard);
                if(tempMove <= bestMoveScore) {
                    bestMoveScore = tempMove;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '-';
            }
        }
    }

    return bestMoveScore;
}

Move Game::minimax(char AIboard[3][3]) {
    int bestMoveScore = 100; // -100 is arbitrary
    Move bestMove;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = ai;
                int tempMoveScore = maxSearch(AIboard);
                if(tempMoveScore <= bestMoveScore) {
                    bestMoveScore = tempMoveScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                AIboard[i][j] = '-';
            }
        }
    }

    return bestMove;
}

int Game::score() {
    if(checkWin(HUMAN)) { return 10; }
    else if(checkWin(AI)) { return -10; }
    return 0; // draw
}

bool Game::checkWin(Player player) {
    char playerChar;
    if(player == HUMAN) playerChar = human;
    else playerChar = ai;

    for(int i = 0; i < 3; i++) {
        // Check horizontals
        if(gameBoard[i][0] == playerChar && gameBoard[i][1] == playerChar
           && gameBoard[i][2] == playerChar)
            return true;

        // Check verticals
        if(gameBoard[0][i] == playerChar && gameBoard[1][i] == playerChar
           && gameBoard[2][i] == playerChar)
            return true;
    }

    // Check diagonals
    if (gameBoard[0][0] == playerChar && gameBoard[1][1] == playerChar
        && gameBoard[2][2] == playerChar) {
        return true;
    } else if (gameBoard[0][2] == playerChar && gameBoard[1][1] == playerChar
               && gameBoard[2][0] == playerChar) {
        return true;
    }

    return false;
}

bool Game::gameOver() {
    if(checkWin(HUMAN)) return true;
    else if(checkWin(AI)) return true;

    bool emptySpace = false;
    for(int i = 0; i < 3; i++) {
        if(gameBoard[i][0] == '-' || gameBoard[i][1] == '-' || gameBoard[i][2] == '-')
            emptySpace = true;
    }
    return !emptySpace;
}
