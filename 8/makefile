# Define the compiler
CXX = g++

# Define the flags for the compiler
CXXFLAGS = -Wall -pthread

# Define the source files
SRCS = main.cpp proactor.cpp

# Define the object files
OBJS = main.o proactor.o

# Define the output executable
TARGET = server

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
main.o: main.cpp proactor.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

proactor.o: proactor.cpp proactor.hpp
	$(CXX) $(CXXFLAGS) -c proactor.cpp

# Rule to clean the build directory
clean:
	rm -f $(TARGET) $(OBJS)
