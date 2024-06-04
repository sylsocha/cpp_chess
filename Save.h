#ifndef SAVE_H
#define SAVE_H

#include "ChessBoard.h"

class Save {
public:
    static void saveGame(const ChessBoard& board, const std::string& filename);
    static void loadGame(ChessBoard& board, const std::string& filename);
};

#endif // SAVE_H
