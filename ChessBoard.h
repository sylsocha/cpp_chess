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
    void movePiece(int startX, int startY, int endX, int endY);
    bool isInCheck(bool white) const;
    bool unChecked(bool white, int startX, int startY, int endX, int endY) const;
    bool isCheckmate(bool white) const;
    bool isStalemate(bool white) const;

private:
    std::vector<std::vector<Piece*>> board;
    void setupPieces();
};

#endif // CHESSBOARD_H
