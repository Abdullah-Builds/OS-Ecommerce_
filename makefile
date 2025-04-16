# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Source files
SRC = auth.cpp menu.cpp Inventory.cpp dining_philosophy.cpp loader.cpp main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable name (not a .cpp file!)
TARGET = app

# Libraries
LIBS = -lsqlite3 -pthread

# Default build target
all: $(TARGET)

# Link object files to make final binary
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

