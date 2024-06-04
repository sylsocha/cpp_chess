#ifndef GAME_H
#define GAME_H

#include "ChessBoard.h"

class Game {
public:
    Game();
    void play();

private:
    ChessBoard board;
    bool whiteTurn;
    void displayBoard() const;
    int handleUserInput();
    void switchTurn();
};

#endif // GAME_H
