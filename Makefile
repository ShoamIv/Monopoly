CXX = clang++
CXXFLAGS = -std=c++17 -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=99

# Define the sources for the main executable (excluding test files)
SOURCES = Board.cpp ChanceCard.cpp Dice.cpp Estate.cpp GameFlow.cpp Infrastructure.cpp SpecialSquare.cpp \
          Square.cpp Player.cpp Street.cpp Button.cpp

# Define the headers
HEADERS = Board.hpp ChanceCard.hpp Dice.hpp Estate.hpp GameFlow.hpp Infrastructure.hpp SpecialSquare.hpp \
          Square.hpp Player.hpp Street.hpp Button.hpp

# Define the main sources (including main.cpp)
MAIN_SOURCES = $(SOURCES) main.cpp

# Define the test sources (including test files)
TEST_SOURCES = $(SOURCES) Test.cpp TestCounter.cpp

# Define the object files for the main and test executables
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Define the executables
EXECUTABLE = MonopolyGame
TEST_EXECUTABLE = run_tests

# SFML Libraries to link
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Default rule
all: $(EXECUTABLE)

# Run tests rule
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Rule for linking the main executable
$(EXECUTABLE): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Rule for linking the test executable
$(TEST_EXECUTABLE): $(filter-out main.o,$(TEST_OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Rule for compiling object files with corresponding headers
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling object files without corresponding headers
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind_test: $(TEST_EXECUTABLE)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TEST_EXECUTABLE)

valgrind_catan: $(EXECUTABLE)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(EXECUTABLE)
#2>&1 | { egrep "lost| at " || true; }

# Clean rule
clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)
