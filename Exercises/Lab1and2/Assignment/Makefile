# Makefile for Assignment 1
# Compiles AnalyseData program with CustomFunctions

CXX = g++
CXXFLAGS = -std=c++20 -Wall
TARGET = AnalyseData
SOURCES = AnalyseData.cxx CustomFunctions.cxx
HEADERS = CustomFunctions.h

# Default target - builds the executable
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Build successful! Run with ./$(TARGET)"

# Clean up compiled files
clean:
	rm -f $(TARGET) *.o
	@echo "Cleaned up build files"

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
