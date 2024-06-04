#include "Game.h"
#include <iostream>

Game::Game() : whiteTurn(true) {}

void Game::play() {
    while (true) {
        displayBoard();
        std::cout << "Your turn " << (whiteTurn ? "White" : "Black") << std::endl;
        int userInput = handleUserInput();
        if (userInput == 0) {
            break; // Koniec gry, jeśli gracz zrezygnował
        }
        else if (userInput == 1){
            switchTurn();   //Dopuszczalny ruch -> teraz przeciwnik
        }


/*
        //Szach-mat
        if (board.isCheckmate(whiteTurn)) {
            std::cout << "Checkmate! ";
            std::cout << (whiteTurn ? "Black" : "White") << " wins.\n";
            break; // Zakończ grę po szach-macie
        }
        */
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
                std::cout << "-  "; //Puste pola na szachownicy
            }
        }
        std::cout << std::endl;
    }
}

std::vector<int> convertToInt(const std::string& input){    //konwertuje ruchy gracza do używanych przez program indexów tabeli
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

int Game::handleUserInput() {
    std::string moveChars;
    int startX, startY, endX, endY;

    std::cout << "Your move: ";
    std::cin >> moveChars;

    if (moveChars == "quit") {
        board.movePiece(-1, -1, -1, -1); //Rezygnacja w gry poprzez wpisanie quit
        return 0;
    }
    else {
        std::vector<int> converted = convertToInt(moveChars);

        startX = converted[0];
        startY = converted[1];
        endX = converted[2];
        endY = converted[3];

        Piece *piece = board.getPieceAt(startX, startY);
        Piece *targetPiece = board.getPieceAt(endX, endY);
        if (piece && piece->isWhite() == whiteTurn && piece->isValidMove(startX, startY, endX, endY, board)) {  //ruch jest możliwy gdy pierwsza pozycja ma fiurę należącą do danego gracza i można nią wykonać podany ruch
            if (dynamic_cast<King*>(targetPiece) && targetPiece->isWhite() != whiteTurn) {
                std::cout << "You cannot capture the king!\n";
                return 2; // Nieprawidłowy ruch (próba zbijania króla)
            }
            else if(board.isInCheck(piece->isWhite())){ //król gracza pod szachem -> ruch musi usunąć szach
                if(board.unChecked(piece->isWhite(), startX, startY, endX, endY)) {
                    board.movePiece(startX, startY, endX, endY);
                    return 1;
                }
                else{
                    std::cout << "This move leaves kings under check!" << std::endl;
                    return 2;
                }

            }
            else{
                board.movePiece(startX, startY, endX, endY);
                if(board.isInCheck(!piece->isWhite())) std::cout << "Check!" << std::endl;
                return 1;
            }
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
            return 2;
        }
    }
}


void Game::switchTurn() {
    whiteTurn = !whiteTurn;
}

