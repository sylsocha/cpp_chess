#include "ChessBoard.h"
#include <iostream>

ChessBoard::ChessBoard() {
    initializeBoard();
}

ChessBoard::~ChessBoard() {
    for (auto& row : board) {
        for (auto& piece : row) {
            delete piece;
        }
    }
}

void ChessBoard::initializeBoard() {
    board.resize(8, std::vector<Piece*>(8, nullptr));
    setupPieces();
}

void ChessBoard::setupPieces() {    // Inicjalizacja figur na planszy

     board[0][0] = new Rook(true);
     board[0][1] = new Knight(true);
     board[0][2] = new Bishop(true);
     board[0][3] = new Queen(true);
     board[0][4] = new King(true);
     board[0][5] = new Bishop(true);
     board[0][6] = new Knight(true);
     board[0][7] = new Rook(true);

     for(int i = 0; i<8; i++){
         board[1][i] = new Pawn(true);
     }

    board[7][0] = new Rook(false);
    board[7][1] = new Knight(false);
    board[7][2] = new Bishop(false);
    board[7][3] = new Queen(false);
    board[7][4] = new King(false);
    board[7][5] = new Bishop(false);
    board[7][6] = new Knight(false);
    board[7][7] = new Rook(false);

    for(int i = 0; i<8; i++){
        board[6][i] = new Pawn(false);
    }

}

Piece* ChessBoard::getPieceAt(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return nullptr;
    }
    return board[y][x];
}

void ChessBoard::movePiece(int startX, int startY, int endX, int endY) {

    if (startX == -1 && startY == -1 && endX == -1 && endY == -1) {
        std::cout << "Player resigned. Game over.\n";
    }

    Piece* piece = board[startY][startX];
    Piece* targetPiece = board[endY][endX];


    if (targetPiece != nullptr) {
        std::cout << "Capturing piece: " << targetPiece->getSymbol() << std::endl;
    }

    // Wykonanie ruchu
    board[endY][endX] = piece;
    board[startY][startX] = nullptr;

    // Aktualizacja pozycji figury
    piece->setPosition(endX, endY);
}


bool ChessBoard::isInCheck(bool white) const {
    int kingX = -1, kingY = -1;
    char kingSymbol = white ? 'K' : 'k';

    for (int y = 0; y < 8; ++y) {   //szukanie pozycji króla
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board[y][x];
            if (piece != nullptr && piece->isWhite() == white && piece->getSymbol()[0] == kingSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board[y][x];
            if (piece != nullptr && piece->isWhite() != white) {
                if (piece->isValidMove(x, y, kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}



bool ChessBoard::unChecked(bool white, int startX, int startY, int endX, int endY) const{
    ChessBoard tempBoard = *this;
    std::cout << "TEMPORARY 1\n";
    std::cout << "  ";
    std::cout << "A  B  C  D  E  F  G  H" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout<<8-y << " ";
        for (int x = 0; x < 8; ++x) {
            Piece* piece = tempBoard.getPieceAt(x, y);
            if (piece) {
                std::cout << piece->getSymbol() << "  ";
            } else {
                std::cout << "-  "; //Puste pola na szachownicy
            }
        }
        std::cout << std::endl;
    }

    tempBoard.movePiece(startX, startY, endX, endY);

    std::cout << "TEMPORARY 2\n";
    std::cout << "  ";
    std::cout << "A  B  C  D  E  F  G  H" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout<<8-y << " ";
        for (int x = 0; x < 8; ++x) {
            Piece* piece = tempBoard.getPieceAt(x, y);
            if (piece) {
                std::cout << piece->getSymbol() << "  ";
            } else {
                std::cout << "-  "; //Puste pola na szachownicy
            }
        }
        std::cout << std::endl;
    }


    // Sprawdzenie, czy król nadal jest w szachu
    std::cout << tempBoard.isInCheck(white);


    return false;

}


bool ChessBoard::isCheckmate(bool white) const {
    if (!isInCheck(white)) {
        return false;
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board[y][x];
            if (piece != nullptr && piece->isWhite() == white) {
                for (int newY = 0; newY < 8; ++newY) {
                    for (int newX = 0; newX < 8; ++newX) {
                        if (piece->isValidMove(x, y, newX, newY, *this)) {
                            // Kopia planszy
                            ChessBoard tempBoard = *this;
                            tempBoard.board[newY][newX] = tempBoard.board[y][x];
                            tempBoard.board[y][x] = nullptr;

                            // Sprawdzenie, czy król nadal jest w szachu
                            if (!tempBoard.isInCheck(white)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessBoard::isStalemate(bool white) const {
    if (isInCheck(white)) {
        return false;
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board[y][x];
            if (piece != nullptr && piece->isWhite() == white) {
                for (int newY = 0; newY < 8; ++newY) {
                    for (int newX = 0; newX < 8; ++newX) {
                        if (piece->isValidMove(x, y, newX, newY, *this)) {
                            // Kopia planszy
                            ChessBoard tempBoard = *this;
                            tempBoard.board[newY][newX] = tempBoard.board[y][x];
                            tempBoard.board[y][x] = nullptr;

                            // Sprawdzenie, czy król nadal jest w szachu
                            if (!tempBoard.isInCheck(white)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
