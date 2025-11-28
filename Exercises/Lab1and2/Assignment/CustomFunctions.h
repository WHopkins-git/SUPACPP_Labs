// CustomFunctions.h
// Header file for data analysis functions
// Date: 28th November 2025

#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <string>
#include <utility>

// Function to read 2D coordinate data from file
// Returns a vector of pairs representing (x,y) coordinates
std::vector<std::pair<double, double>> readDataFile(const std::string& filename);

// Function to read error data from file
std::vector<std::pair<double, double>> readErrorFile(const std::string& filename);

// Print first N lines of data to terminal
void printNLines(const std::vector<std::pair<double, double>>& data, int N);

// Calculate magnitude of each vector (treating each point as position vector from origin)
std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data);

// Fit straight line to data using least squares method
// Returns parameters (slope, intercept) and chi-squared/NDOF
std::pair<std::pair<double, double>, double> fitStraightLine(
    const std::vector<std::pair<double, double>>& data,
    const std::vector<std::pair<double, double>>& errors);

// Calculate x^y using recursion (y rounded to nearest integer)
// Base case for y=0, y=1, and recursive for other values
double powerRecursive(double x, double y);

// Helper function for recursive power calculation
double powerHelper(double base, int exponent);

// Overloaded print functions for different data types
void printToTerminal(const std::vector<std::pair<double, double>>& data, int N);
void printToTerminal(const std::vector<double>& values, const std::string& label);
void printToTerminal(const std::pair<std::pair<double, double>, double>& fitResult);

// Overloaded save functions for writing results to files
void saveToFile(const std::vector<std::pair<double, double>>& data, int N, const std::string& filename);
void saveToFile(const std::vector<double>& values, const std::string& filename, const std::string& label);
void saveToFile(const std::pair<std::pair<double, double>, double>& fitResult, const std::string& filename);

#endif
