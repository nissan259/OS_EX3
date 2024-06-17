# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Executable name
EXEC = kosaraju

# Source files
SRCS = Kosaraju.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)

# Rule to link object files into executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Rule to compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target to clean the project
clean:
	rm -f $(OBJS) $(EXEC)
