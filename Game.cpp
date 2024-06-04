#include "Game.h"
#include <iostream>

Game::Game() : whiteTurn(true) {}

void Game::play() {
    while (true) {
        displayBoard();
        handleUserInput();
        switchTurn();
    }
}

void Game::displayBoard() const {
    std::cout << "  ";
    std::cout << "A  B  C  D  E  F  G  H" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout<<8-y << " ";
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board.getPieceAt(x, y);
            if (piece) {
                std::cout << piece->getSymbol() << "  ";
            } else {
                std::cout << ".  ";
            }
        }
        std::cout << std::endl;
    }
}

std::vector<int> convertToInt(const std::string& input){
    std::vector<int> toReturn;

    const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    const char numbers[] = {'8', '7', '6', '5', '4', '3', '2', '1'};

    for(char c : input){
        if(c == ' '){
            continue;
        }
        else{
            for(int i = 0; i<8; i++){
                if(c == letters[i] || c == numbers[i]){
                    toReturn.push_back(i);
                    break;
                }
            }
        }
    }

    return toReturn;
}

void Game::handleUserInput() {
    std::string moveChars;
    int startX, startY, endX, endY;
    std::cout << "Your move: ";
    std::cin >> moveChars;

    std::vector<int> converted = convertToInt(moveChars);

    startX = converted[0];
    startY = converted[1];
    endX = converted[2];
    endY = converted[3];

    Piece* piece = board.getPieceAt(startX, startY);
    if (piece && piece->isWhite() == whiteTurn && piece->isValidMove(startX, startY, endX, endY, board)) {
        board.movePiece(startX, startY, endX, endY);
    } else {
        std::cout << "Invalid move. Try again." << std::endl;
    }

}

void Game::switchTurn() {
    whiteTurn = !whiteTurn;
}

