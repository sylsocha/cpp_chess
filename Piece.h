#ifndef PIECE_H
#define PIECE_H

#include <string>
class ChessBoard;

class Piece {
public:
    virtual ~Piece() {}
    virtual bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getSymbol() const = 0;
    bool isWhite() const { return white; }
    void setPosition(int x, int y) { posX = x; posY = y; }


protected:
    Piece(bool isWhite) : white(isWhite) {}
    bool white;
    int posX;
    int posY;
};

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "Pawn"; }
    std::string getSymbol() const override { return white ? "P" : "p"; }
};

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "Rook"; }
    std::string getSymbol() const override { return white ? "R" : "r"; }
};

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "Knight"; }
    std::string getSymbol() const override { return white ? "N" : "n"; }
};

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "Bishop"; }
    std::string getSymbol() const override { return white ? "B" : "b"; }
};

class Queen : public Piece {
public:
    Queen(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "Queen"; }
    std::string getSymbol() const override { return white ? "Q" : "q"; }
};

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
    std::string getName() const override { return "King"; }
    std::string getSymbol() const override { return white ? "K" : "k"; }
};

#endif // PIECE_H
