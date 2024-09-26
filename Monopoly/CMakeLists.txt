cmake_minimum_required(VERSION 3.28)
project(Monopoly)

set(CMAKE_CXX_STANDARD 17)

# Main executable for Monopoly game
add_executable(Monopoly
        main.cpp
        Square.cpp
        Square.hpp
        Estate.cpp
        Estate.hpp
        Player.cpp
        Player.hpp
        Board.cpp
        Board.hpp
        SpecialSquare.cpp
        SpecialSquare.hpp
        Street.cpp
        Street.hpp
        Infrastructure.cpp
        Infrastructure.hpp
        ChanceCard.cpp
        ChanceCard.hpp
        GameFlow.cpp
        GameFlow.hpp
        Dice.cpp
        Dice.hpp
)

# Test executable
add_executable(Monopoly_tests
        Test.cpp
        TestCounter.cpp
        Square.cpp           # Include implementation files
        Board.cpp            # Include implementation files
        SpecialSquare.cpp    # Include implementation files
        Street.cpp          # Include implementation files
        Infrastructure.cpp    # Include implementation files
        GameFlow.cpp         # Include implementation files
        Player.cpp           # Include Player implementation
        Dice.cpp             # Include Dice implementation
        Estate.cpp           # Include Estate implementation
)

# Optionally, you can add linking to your testing framework here if needed
# For example, if using doctest:
# target_link_libraries(Monopoly_tests PRIVATE doctest)
