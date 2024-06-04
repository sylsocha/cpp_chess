#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include "Piece.h"

class ChessBoard {
public:
    ChessBoard();
    ~ChessBoard();

    void initializeBoard();
    Piece* getPieceAt(int x, int y) const;
    bool movePiece(int startX, int startY, int endX, int endY);

private:
    std::vector<std::vector<Piece*>> board;
    void setupPieces();
};

#endif // CHESSBOARD_H
