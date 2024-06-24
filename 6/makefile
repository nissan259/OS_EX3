# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = server
SRC = server.cpp Reactor.cpp  # Add the file that contains the Reactor class implementation

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Rule to clean the directory
clean:
	rm -f $(TARGET)