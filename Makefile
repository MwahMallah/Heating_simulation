# Name of the output executable
TARGET = main

# Compiler to use
CXX = g++

# Compiler flags: enable warnings and set the C++ standard to C++17
CXXFLAGS = -Wall -Wextra -std=c++17

DEBUGFLAGS = -DDEBUG

# Source files
SRC = Utils.cpp Environment.cpp Collector.cpp main.cpp 

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

debug: $(SRC)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)
