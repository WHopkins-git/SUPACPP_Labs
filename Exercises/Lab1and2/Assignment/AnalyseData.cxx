// AnalyseData.cxx
// 
// Author: William Hopkins
// Date: 28th November 2025
//
// This program reads (x,y) coordinate data from a file and performs various
// analyses including printing data, calculating magnitudes, fitting curves,
// and computing power functions.

#include "CustomFunctions.h"
#include <iostream>
#include <vector>
#include <string>

// Display menu options to user
void displayMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "    Data Analysis Tool" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1. Print first N lines of data" << std::endl;
    std::cout << "2. Calculate magnitudes of all data points" << std::endl;
    std::cout << "3. Fit straight line using least squares" << std::endl;
    std::cout << "4. Calculate x^y for each data point" << std::endl;
    std::cout << "5. Exit program" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

int main() {
    // File paths - relative to current directory
    std::string dataFile = "../input2D_float.txt";
    std::string errorFile = "../error2D_float.txt";

    // Read the data files at startup
    std::cout << "Loading data from file..." << std::endl;
    std::vector<std::pair<double, double>> data = readDataFile(dataFile);

    if (data.empty()) {
        std::cerr << "Error: No data loaded. Please check the file path." << std::endl;
        return 1;
    }

    std::cout << "Successfully loaded " << data.size() << " data points!" << std::endl;

    // Main program loop
    bool running = true;

    while (running) {
        displayMenu();

        int choice;
        std::cin >> choice;

        // Clear any bad input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5." << std::endl;
            continue;
        }

        switch (choice) {
            case 1: {
                // Print first N lines
                std::cout << "\nHow many lines would you like to print? ";
                int N;
                std::cin >> N;

                printToTerminal(data, N);

                // Save to file
                std::string filename = "output_first_N_lines.txt";
                saveToFile(data, N, filename);

                break;
            }

            case 2: {
                // Calculate and display magnitudes
                std::cout << "\nCalculating magnitudes..." << std::endl;
                std::vector<double> magnitudes = calculateMagnitudes(data);

                printToTerminal(magnitudes, "Magnitude of each data point");

                // Save to file
                std::string filename = "output_magnitudes.txt";
                saveToFile(magnitudes, filename, "Magnitude of each data point");

                break;
            }

            case 3: {
                // Fit straight line with chi-squared analysis
                std::cout << "\nFitting straight line to data..." << std::endl;

                // Need to load error data for chi-squared calculation
                std::vector<std::pair<double, double>> errors = readErrorFile(errorFile);

                if (errors.size() != data.size()) {
                    std::cerr << "Error: Mismatch between data and error file sizes." << std::endl;
                    break;
                }

                std::pair<std::pair<double, double>, double> fitResult = fitStraightLine(data, errors);

                printToTerminal(fitResult);

                // Save to file
                std::string filename = "output_fit_results.txt";
                saveToFile(fitResult, filename);

                break;
            }

            case 4: {
                // Calculate x^y for each data point
                std::cout << "\nCalculating x^y for each data point (recursively)..." << std::endl;

                std::vector<double> powerResults;
                for (const auto& point : data) {
                    double x = point.first;
                    double y = point.second;
                    double result = powerRecursive(x, y);
                    powerResults.push_back(result);
                }

                printToTerminal(powerResults, "Power calculation results (x^y with y rounded)");

                // Save to file
                std::string filename = "output_power_results.txt";
                saveToFile(powerResults, filename, "Power calculation results (x^y with y rounded)");

                break;
            }

            case 5: {
                // Exit program
                std::cout << "\nExiting program. Goodbye!" << std::endl;
                running = false;
                break;
            }

            default: {
                std::cout << "\nInvalid choice. Please enter a number between 1 and 5." << std::endl;
                break;
            }
        }

        // Add some spacing for readability
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    return 0;
}
