// CustomFunctions.cxx
// Implementation of data analysis functions
// Date: 28th November 2025

#include "CustomFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

// Read data from CSV file containing x,y coordinates
std::vector<std::pair<double, double>> readDataFile(const std::string& filename) {
    std::vector<std::pair<double, double>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    // Read data line by line
    while (std::getline(file, line)) {
        if (line.empty()) continue; // skip empty lines

        std::stringstream ss(line);
        std::string x_str, y_str;

        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
            double x = std::stod(x_str);
            double y = std::stod(y_str);
            data.push_back(std::make_pair(x, y));
        }
    }

    file.close();
    return data;
}

// Read error data from file (same format as data file)
std::vector<std::pair<double, double>> readErrorFile(const std::string& filename) {
    return readDataFile(filename); // same structure as data file
}

// Print first N lines to terminal with proper edge case handling
void printNLines(const std::vector<std::pair<double, double>>& data, int N) {
    int numLines = N;

    // Edge case: if N is larger than data size, warn user and print only first 5
    if (N > static_cast<int>(data.size())) {
        std::cout << "Warning: Requested " << N << " lines but only "
                  << data.size() << " data points available." << std::endl;
        std::cout << "Printing first 5 lines instead." << std::endl;
        numLines = std::min(5, static_cast<int>(data.size()));
    }

    std::cout << "\nData points (x, y):" << std::endl;
    std::cout << "-------------------" << std::endl;
    for (int i = 0; i < numLines; i++) {
        std::cout << "Point " << (i+1) << ": ("
                  << data[i].first << ", "
                  << data[i].second << ")" << std::endl;
    }
}

// Calculate magnitude of each (x,y) point treated as a vector from origin
// Using the standard Euclidean norm: |v| = sqrt(x^2 + y^2)
std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data) {
    std::vector<double> magnitudes;

    for (const auto& point : data) {
        double x = point.first;
        double y = point.second;
        // Calculate magnitude using Pythagorean theorem
        double magnitude = std::sqrt(x*x + y*y);
        magnitudes.push_back(magnitude);
    }

    return magnitudes;
}

// Fit a straight line y = px + q using least squares method
// Also calculate chi-squared/NDOF to assess goodness of fit
std::pair<std::pair<double, double>, double> fitStraightLine(
    const std::vector<std::pair<double, double>>& data,
    const std::vector<std::pair<double, double>>& errors) {

    int N = data.size();

    // Calculate sums needed for least squares formulas
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;

    for (const auto& point : data) {
        double x = point.first;
        double y = point.second;
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

    // Apply least squares formulas to get slope (p) and intercept (q)
    // p = (N*sum(xy) - sum(x)*sum(y)) / (N*sum(x^2) - sum(x)*sum(x))
    double p = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x);

    // q = (sum(x^2)*sum(y) - sum(xy)*sum(x)) / (N*sum(x^2) - sum(x)*sum(x))
    double q = (sum_x2 * sum_y - sum_xy * sum_x) / (N * sum_x2 - sum_x * sum_x);

    // Calculate chi-squared: sum of (observed - expected)^2 / sigma^2
    double chi_squared = 0.0;

    for (size_t i = 0; i < data.size(); i++) {
        double x_obs = data[i].first;
        double y_obs = data[i].second;
        double y_expected = p * x_obs + q; // fitted line value

        // Use y-component of error as sigma
        double sigma = errors[i].second;

        // Add contribution to chi-squared
        double residual = (y_obs - y_expected) / sigma;
        chi_squared += residual * residual;
    }

    // Calculate chi-squared per degree of freedom
    // NDOF = N - number_of_parameters, for straight line we have 2 parameters (p and q)
    int ndof = N - 2;
    double chi2_ndof = chi_squared / ndof;

    return std::make_pair(std::make_pair(p, q), chi2_ndof);
}

// Helper function for recursive power calculation with integer exponent
double powerHelper(double base, int exponent) {
    // Base cases
    if (exponent == 0) return 1.0;
    if (exponent == 1) return base;

    // Handle negative exponents
    if (exponent < 0) {
        return 1.0 / powerHelper(base, -exponent);
    }

    // Recursive case: x^n = x * x^(n-1)
    return base * powerHelper(base, exponent - 1);
}

// Calculate x^y where y is rounded to nearest integer, using recursion
double powerRecursive(double x, double y) {
    // Round y to nearest integer
    int y_rounded = static_cast<int>(std::round(y));

    // Use recursive helper function
    return powerHelper(x, y_rounded);
}

// ========== Overloaded print functions ==========

// Print N lines of data to terminal
void printToTerminal(const std::vector<std::pair<double, double>>& data, int N) {
    printNLines(data, N);
}

// Print vector of doubles with a label
void printToTerminal(const std::vector<double>& values, const std::string& label) {
    std::cout << "\n" << label << ":" << std::endl;
    std::cout << std::string(label.length() + 1, '-') << std::endl;
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << "Point " << (i+1) << ": "
                  << std::setprecision(8) << values[i] << std::endl;
    }
}

// Print fit results to terminal
void printToTerminal(const std::pair<std::pair<double, double>, double>& fitResult) {
    double p = fitResult.first.first;
    double q = fitResult.first.second;
    double chi2_ndof = fitResult.second;

    std::cout << "\nLeast Squares Fit Results:" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Fitted line: y = " << p << " * x + " << q << std::endl;
    std::cout << "Chi-squared/NDOF = " << chi2_ndof << std::endl;

    // Comment on fit quality (since we expect it to be bad)
    if (chi2_ndof > 2.0) {
        std::cout << "Note: Large chi-squared/NDOF indicates poor fit (as expected!)" << std::endl;
    }
}

// ========== Overloaded save to file functions ==========

// Save N lines of data to file
void saveToFile(const std::vector<std::pair<double, double>>& data, int N, const std::string& filename) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    int numLines = std::min(N, static_cast<int>(data.size()));
    if (N > static_cast<int>(data.size())) {
        numLines = std::min(5, static_cast<int>(data.size()));
    }

    outfile << "First " << numLines << " data points (x, y):" << std::endl;
    for (int i = 0; i < numLines; i++) {
        outfile << data[i].first << ", " << data[i].second << std::endl;
    }

    outfile.close();
    std::cout << "Data saved to " << filename << std::endl;
}

// Save vector of doubles to file with a label
void saveToFile(const std::vector<double>& values, const std::string& filename, const std::string& label) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    outfile << label << ":" << std::endl;
    for (size_t i = 0; i < values.size(); i++) {
        outfile << std::setprecision(8) << values[i] << std::endl;
    }

    outfile.close();
    std::cout << "Results saved to " << filename << std::endl;
}

// Save fit results to file
void saveToFile(const std::pair<std::pair<double, double>, double>& fitResult, const std::string& filename) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    double p = fitResult.first.first;
    double q = fitResult.first.second;
    double chi2_ndof = fitResult.second;

    outfile << "Least Squares Fit Results:" << std::endl;
    outfile << "Fitted line: y = " << p << " * x + " << q << std::endl;
    outfile << "Chi-squared/NDOF = " << chi2_ndof << std::endl;

    outfile.close();
    std::cout << "Fit results saved to " << filename << std::endl;
}
