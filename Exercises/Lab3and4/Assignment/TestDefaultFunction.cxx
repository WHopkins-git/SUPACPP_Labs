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
    std::string plots_dir = "Plots";
    if (!std::filesystem::exists(plots_dir)) {
        std::filesystem::create_directories(plots_dir);
        std::cout << "Created " << plots_dir << "/ directory for output plots\n" << std::endl;
    }

    // Find the mystery data file in Data/ directory (at repository root)
    std::string datafile;
    std::string data_dir = "../../../Data/";

    // Check if directory exists
    if (!std::filesystem::exists(data_dir)) {
        std::cerr << "Error: Directory " << data_dir << " does not exist!" << std::endl;
        std::cerr << "Please run the following first:" << std::endl;
        std::cerr << "  cd .." << std::endl;
        std::cerr << "  ./GenerateRandomData" << std::endl;
        return 1;
    }

    // Look for MysteryData*.txt file
    for (const auto& entry : std::filesystem::directory_iterator(data_dir)) {
        if (entry.path().filename().string().find("MysteryData") != std::string::npos &&
            entry.path().extension() == ".txt") {
            datafile = entry.path().string();
            std::cout << "Found mystery data file: " << entry.path().filename() << "\n" << std::endl;
            break;
        }
    }

    if (datafile.empty()) {
        std::cerr << "Error: No mystery data file found in " << data_dir << std::endl;
        std::cerr << "Please run ../GenerateRandomData first!" << std::endl;
        return 1;
    }

    // Load mystery data
    std::vector<double> mystery_data = readMysteryData(datafile);

    if (mystery_data.empty()) {
        std::cerr << "No data loaded. Exiting." << std::endl;
        return 1;
    }

    // Create FiniteFunction object with explicit parameters
    // Uses range [-10, 10] and invxsquared function: f(x) = 1/(1+x^2)
    {
        FiniteFunction default_function(-10.0, 10.0, "DefaultFunction");

        // Print function information
        std::cout << "=== Default FiniteFunction ===" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        // Calculate integral for normalization
        int n_divisions = 1000;
        default_function.integral(n_divisions);

        std::cout << "After normalization:" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        // Plot the function (uses default range from constructor)
        default_function.plotFunction();

        // Plot the data alongside the function
        // Using 50 bins for histogram
        // Make a copy to avoid any potential reference issues
        std::vector<double> data_copy = mystery_data;
        int n_bins = 50;
        default_function.plotData(data_copy, n_bins);

        std::cout << "\n========================================" << std::endl;
        std::cout << "Plot generation in progress..." << std::endl;
        // Destructor will be called here, which generates the plot
    }

    std::cout << "Plot saved to Plots/DefaultFunction.png" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
