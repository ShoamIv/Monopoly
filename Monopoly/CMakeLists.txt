cmake_minimum_required(VERSION 3.28)
project(Monopoly)

set(CMAKE_CXX_STANDARD 17)

add_executable(Monopoly main.cpp
        Square.cpp
        Square.h++
        Estate.cpp
        Estate.h++
        Player.cpp
        Player.h++
        Board.cpp
        Board.h++
        SpecialSquare.cpp
        SpecialSquare.h++
        Streets.cpp
        Street.h++
        Infrastructure.cpp
        Infrastructure.h++
        ChanceCard.cpp
        ChanceCard.h++
        GameFlow.cpp
        GameFlow.h++
        Dice.cpp
        Dice.h++
        Test.cpp
)
