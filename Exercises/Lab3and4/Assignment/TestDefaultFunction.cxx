// TestDefaultFunction.cxx
// Test default FiniteFunction class
// William Hopkins
// December 2024

#include "../FiniteFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

// Read data from file
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

    if (!std::filesystem::exists("Plots")) {
        std::filesystem::create_directories("Plots");
    }

    std::string datafile = "../../../Data/MysteryData22012.txt";
    std::vector<double> mystery_data = readMysteryData(datafile);

    if (mystery_data.empty()) {
        std::cerr << "No data loaded. Exiting." << std::endl;
        return 1;
    }

    {
        FiniteFunction default_function(-10.0, 10.0, "DefaultFunction");

        std::cout << "=== Default FiniteFunction ===" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        default_function.integral(1000);

        std::cout << "After normalization:" << std::endl;
        default_function.printInfo();
        std::cout << std::endl;

        // Plot function and data
        default_function.plotFunction();
        default_function.plotData(mystery_data, 50);

        std::cout << "\n========================================" << std::endl;
        std::cout << "Plot generation in progress..." << std::endl;
    }

    std::cout << "Plot saved to Plots/DefaultFunction.png" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
