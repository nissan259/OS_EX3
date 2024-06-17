# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pg

# Define the target executable
TARGET = scc_finder

# Define the source files
SRCS = main.cpp kosaraju-sharir.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build artifacts
clean:
	rm -f $(TARGET) $(OBJS) gmon.out

# Rule to run the program with input redirection from input.txt
run: $(TARGET)
	./$(TARGET) < input.txt

.PHONY: all clean run
