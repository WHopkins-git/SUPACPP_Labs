# Makefile for Assignment 2 - Distribution Fitting
# Compiles test program with custom distributions and FiniteFunctions

CXX = g++
CXXFLAGS = -std=c++20 -Wall -I../../../GNUplot/
LDFLAGS = -lboost_iostreams -lboost_system -lboost_filesystem

# Source files
SOURCES = TestDistributions.cxx Distributions.cxx ../FiniteFunctions.cxx
HEADERS = Distributions.h ../FiniteFunctions.h
TARGET = TestDistributions

# Default target - builds the executable
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)
	@echo "Build successful! Run with ./$(TARGET)"

# Clean up compiled files
clean:
	rm -f $(TARGET) *.o
	@echo "Cleaned up build files"

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
