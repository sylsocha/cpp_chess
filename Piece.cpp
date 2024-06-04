#include "Piece.h"
#include "ChessBoard.h"

// Implementacja metody isValidMove dla pionka
bool Pawn::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int direction = white ? 1 : -1;
    if (startX == endX && board.getPieceAt(endX, endY) == nullptr) {
        // Move forward by one square
        if (endY == startY + direction) {
            return true;
        }
        // Move forward by two squares from the starting position
        if ((white && startY == 1 || !white && startY == 6) && endY == startY + 2 * direction && board.getPieceAt(endX, startY + direction) == nullptr) {
            return true;
        }
    }
    // Capture diagonally
    if (abs(startX - endX) == 1 && endY == startY + direction && board.getPieceAt(endX, endY) != nullptr && board.getPieceAt(endX, endY)->isWhite() != white) {
        return true;
    }
    return false;
}

// Implementacja metody isValidMove dla wieży
bool Rook::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (startX != endX && startY != endY) return false; // Must move in a straight line
    int stepX = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
    int stepY = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
    int x = startX + stepX;
    int y = startY + stepY;
    while (x != endX || y != endY) {
        if (board.getPieceAt(x, y) != nullptr) return false; // Path must be clear
        x += stepX;
        y += stepY;
    }
    if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
        return true;
    }
    return false;
}

// Implementacja metody isValidMove dla skoczka
bool Knight::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    if (dx * dy == 2) { // Move must be in "L" shape
        if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
            return true;
        }
    }
    return false;
}

// Implementacja metody isValidMove dla gońca
bool Bishop::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (abs(startX - endX) != abs(startY - endY)) return false; // Must move diagonally
    int stepX = (endX - startX) / abs(endX - startX);
    int stepY = (endY - startY) / abs(endY - startY);
    int x = startX + stepX;
    int y = startY + stepY;
    while (x != endX || y != endY) {
        if (board.getPieceAt(x, y) != nullptr) return false; // Path must be clear
        x += stepX;
        y += stepY;
    }
    if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
        return true;
    }
    return false;
}

// Implementacja metody isValidMove dla królowej
bool Queen::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (startX == endX || startY == endY) { // Rook-like move
        int stepX = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
        int stepY = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
        int x = startX + stepX;
        int y = startY + stepY;
        while (x != endX || y != endY) {
            if (board.getPieceAt(x, y) != nullptr) return false; // Path must be clear
            x += stepX;
            y += stepY;
        }
        if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
            return true;
        }
    } else if (abs(startX - endX) == abs(startY - endY)) { // Bishop-like move
        int stepX = (endX - startX) / abs(endX - startX);
        int stepY = (endY - startY) / abs(endY - startY);
        int x = startX + stepX;
        int y = startY + stepY;
        while (x != endX || y != endY) {
            if (board.getPieceAt(x, y) != nullptr) return false; // Path must be clear
            x += stepX;
            y += stepY;
        }
        if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
            return true;
        }
    }
    return false;
}

// Implementacja metody isValidMove dla króla
bool King::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    if (dx <= 1 && dy <= 1) { // King moves only one square in any direction
        if (board.getPieceAt(endX, endY) == nullptr || board.getPieceAt(endX, endY)->isWhite() != white) {
            return true;
        }
    }
    return false;
}
