cmake_minimum_required(VERSION 3.27)
project(cpp_chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_chess
        main.cpp
        ChessBoard.h
        ChessBoard.cpp
        Piece.h
        Piece.cpp
        Game.h
        Game.cpp
        Save.h
        Save.cpp)
