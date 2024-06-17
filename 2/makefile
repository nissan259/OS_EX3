# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pg

# Source files
SRCS = main.cpp Kosarajudeque.cpp

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

# Target for profiling
profile: $(OBJS)
	$(CXX) $(CXXFLAGS) -pg -o $(TARGET) $(OBJS)
	./$(TARGET)   # Run your program with profiling enabled
	gprof $(TARGET) > gprof_output.txt   # Capture gprof output
	./format_gprof.sh   # Run your formatting script

# Clean up build artifacts and gprof output
clean:
	rm -f $(OBJS) $(TARGET) gmon.out gprof_output.txt formatted_gprof.txt

# PHONY targets
.PHONY: clean profile
