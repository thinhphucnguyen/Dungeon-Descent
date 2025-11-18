# Compiler settings
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Target executable
TARGET = game

# Source files (you HAVE Player.cpp, so include it)
SRCS = main.cpp Game.cpp Player.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)
