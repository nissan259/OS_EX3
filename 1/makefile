# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRCS = main.cpp Kosaraju.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = kosaraju

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
