cmake_minimum_required(VERSION 3.10)
project(Monopoly)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the SFML directory
set(SFML_DIR "C:/Users/Shoham/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Add the main Monopoly executable
add_executable(Monopoly
        main.cpp
        Square.cpp
        Estate.cpp
        Player.cpp
        Board.cpp
        SpecialSquare.cpp
        Infrastructure.cpp
        Street.cpp
        ChanceCard.cpp
        GameFlow.cpp
        Dice.cpp
        Button.cpp
)

# Link SFML libraries to the Monopoly executable
target_link_libraries(Monopoly sfml-graphics sfml-window sfml-system)

# Add the Test executable with doctest
add_executable(Test
        Square.cpp
        Estate.cpp
        Player.cpp
        Board.cpp
        SpecialSquare.cpp
        Infrastructure.cpp
        Street.cpp
        ChanceCard.cpp
        GameFlow.cpp
        Dice.cpp
        Button.cpp
       Test.cpp
        TestCounter.cpp
)

# Link SFML libraries to the Test executable if needed
target_link_libraries(Test sfml-graphics sfml-window sfml-system)

# Include the directory for doctest if needed
target_include_directories(Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/path/to/doctest") # Adjust the path accordingly
