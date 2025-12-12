// TestDefaultFunction.cxx
// Test program for default FiniteFunction class
// Tests the invxsquared function: f(x) = 1/(1+x^2)
// Author: SUPA C++ Student
// Date: 11th December 2025

#include "../FiniteFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

// Helper function to read data from mystery data file
std::vector<double> readMysteryData(const std::string& filename) {
    std::vector<double> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    double value;
    while (file >> value) {
        data.push_back(value);
    }

    file.close();
    std::cout << "Read " << data.size() << " data points from " << filename << std::endl;
    return data;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Testing Default FiniteFunction" << std::endl;
    std::cout << "  Function: f(x) = 1/(1+x^2)" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // Create Plots directory if it doesn't exist
    if (!std::filesystem::exists("Plots")) {
        std::filesystem::create_directories("Plots");
    }

    // Specify the mystery data file to use
    std::string datafile = "../../../Data/MysteryData22012.txt";

    // Load mystery data
    std::vector<double> mystery_data = readMysteryData(datafile);

    if (mystery_data.empty()) {
        std::cerr << "No data loaded. Exiting." << std::endl;
        return 1;
    }

    // Create FiniteFunction object
    {
        FiniteFunction default_function(-10.0, 10.0, "DefaultFunction");

        std::cout << "=== Default FiniteFunction ===" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        // Normalize the function
        default_function.integral(1000);

        std::cout << "After normalization:" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        // Plot the function and data
        default_function.plotFunction();
        default_function.plotData(mystery_data, 50);

        std::cout << "\n========================================" << std::endl;
        std::cout << "Plot generation in progress..." << std::endl;
    }

    std::cout << "Plot saved to Plots/DefaultFunction.png" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
