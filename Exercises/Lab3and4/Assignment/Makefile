# Makefile for Assignment 2 - Distribution Fitting
# Compiles test programs with custom distributions and FiniteFunctions

CXX = g++
CXXFLAGS = -std=c++20 -Wall -I../../../GNUplot/
LDFLAGS = -lboost_iostreams -lboost_system -lboost_filesystem

# Source files
DIST_SOURCES = TestDistributions.cxx Distributions.cxx ../FiniteFunctions.cxx
DEFAULT_SOURCES = TestDefaultFunction.cxx ../FiniteFunctions.cxx
HEADERS = Distributions.h ../FiniteFunctions.h
TARGET1 = TestDistributions
TARGET2 = TestDefaultFunction

# Default target - builds both executables
all: $(TARGET1) $(TARGET2)

# Build the distributions test executable
$(TARGET1): $(DIST_SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(DIST_SOURCES) -o $(TARGET1) $(LDFLAGS)
	@echo "Build successful! Run with ./$(TARGET1)"

# Build the default function test executable
$(TARGET2): $(DEFAULT_SOURCES) ../FiniteFunctions.h
	$(CXX) $(CXXFLAGS) $(DEFAULT_SOURCES) -o $(TARGET2) $(LDFLAGS)
	@echo "Build successful! Run with ./$(TARGET2)"

# Clean up compiled files
clean:
	rm -f $(TARGET1) $(TARGET2) *.o
	@echo "Cleaned up build files"

# Run the distributions test
run: $(TARGET1)
	./$(TARGET1)

# Run the default function test
run-default: $(TARGET2)
	./$(TARGET2)

.PHONY: all clean run run-default
