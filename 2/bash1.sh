#!/bin/bash

# Name of the executable
EXECUTABLE="./kosaraju"

# Ensure the executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable $EXECUTABLE not found!"
    exit 1
fi

# Generate input for the program
VERTICES=100000
EDGES=100000
INPUT_FILE="input.txt"

# Generate random graph input
echo "$VERTICES" > $INPUT_FILE
echo "$EDGES" >> $INPUT_FILE
for ((i = 0; i < $EDGES; i++)); do
    # Generate random vertices u and v
    u=$((RANDOM % $VERTICES))
    v=$((RANDOM % $VERTICES))
    echo "$u $v" >> $INPUT_FILE
done

# Run the program with the generated input
cat $INPUT_FILE | $EXECUTABLE

# Check if gmon.out was generated
if [ ! -f "gmon.out" ]; then
    echo "Error: Profiling data gmon.out not found! Ensure the program is compiled with -pg flag."
    exit 1
fi

# Generate profiling report
gprof $EXECUTABLE gmon.out > profile.txt

# Check if gprof2dot is installed and generate the visual profile
if command -v gprof2dot &> /dev/null; then
    gprof $EXECUTABLE gmon.out | gprof2dot | dot -Tpng -o profile.png
    echo "Profiling report generated in profile.txt and profile.png"
else
    echo "Profiling report generated in profile.txt"
    echo "gprof2dot not found, skipping profile.png generation"
fi

