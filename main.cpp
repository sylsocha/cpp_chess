#include <iostream>
#include <locale>
#include "Game.h"

int main() {
    std::cout<<"Welcome to the chess game!\n"
               "To quit type in 'quit'\n"
               "White pieces are represented by capital letters and are at the top of the chessboard.\n"
               "To move a piece, type the position of the piece and the position you want to move it to (e.g. A2A4)\n";
    Game game;
    game.play();

    return 0;
}
