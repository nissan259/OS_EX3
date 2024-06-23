# Source files
SRCS = Main.cpp Reactor.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Executable file
EXEC = reactor_program

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run