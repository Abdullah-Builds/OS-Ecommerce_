# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Isrc -Iinclude

# Source and object files
SRC_DIR = src
INC_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Output binary
TARGET = app

# Libraries
LIBS = -lsqlite3 -pthread

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Compile rule: .cpp -> .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -f $(OBJ) $(TARGET)
