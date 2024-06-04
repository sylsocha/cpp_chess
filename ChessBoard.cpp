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

void ChessBoard::setupPieces() {
    // Inicjalizacja figur na planszy, np.:
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

bool ChessBoard::movePiece(int startX, int startY, int endX, int endY) {
    Piece* piece = getPieceAt(startX, startY);
    if (piece == nullptr) {
        std::cout << "No piece at starting position." << std::endl;
        return false;
    }
    if (!piece->isValidMove(startX, startY, endX, endY, *this)) {
        std::cout << "Invalid move for " << piece->getSymbol() << std::endl;
        return false;
    }
    Piece* targetPiece = getPieceAt(endX, endY);
    if (targetPiece != nullptr) {
        if (targetPiece->isWhite() == piece->isWhite()) {
            std::cout << "Cannot capture own piece." << std::endl;
            return false;
        }
        std::cout << "Capturing piece: " << targetPiece->getSymbol() << std::endl;
        delete targetPiece; // Usunięcie zbitej figury
    }
    board[endY][endX] = piece;
    board[startY][startX] = nullptr;
    piece->setPosition(endX, endY);
    return true;
}
