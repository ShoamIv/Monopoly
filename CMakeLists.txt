cmake_minimum_required(VERSION 3.10)
project(Monopoly)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the SFML directory
set(SFML_DIR "C:/Users/Shoham/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(Monopoly main.cpp Square.cpp Estate.cpp Player.cpp Board.cpp SpecialSquare.cpp Infrastructure.cpp Street.cpp ChanceCard.cpp GameFlow.cpp Dice.cpp Button.cpp)

# Link SFML libraries
target_link_libraries(Monopoly sfml-graphics sfml-window sfml-system)
