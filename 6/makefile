# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Executable
TARGET = server

# Source Files
SRCS = server.cpp reactor.cpp

# Header Files
HEADERS = reactor.h

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Default Rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean Rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony Targets
.PHONY: all clean
