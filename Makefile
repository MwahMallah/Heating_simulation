# Name of the output executable
TARGET = main

# Compiler to use
CXX = g++

# Compiler flags: enable warnings and set the C++ standard to C++17
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SRC = main.cpp

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)
