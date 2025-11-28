// TestDistributions.cxx
// Main program to test custom distributions and find best fit for mystery data
// Author: SUPA C++ Student
// Date: 28th November 2025

#include "../FiniteFunctions.h"
#include "Distributions.h"
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
    std::cout << "  Distribution Testing Program" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // Find the mystery data file in Outputs/data/ directory
    std::string datafile;
    std::string data_dir = "../Outputs/data/";

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

    std::vector<double> mystery_data = readMysteryData(datafile);

    if (mystery_data.empty()) {
        std::cerr << "No data loaded. Exiting." << std::endl;
        return 1;
    }

    // Define range based on data inspection (mystery data seems to be around -5 to 5)
    double range_min = -10.0;
    double range_max = 10.0;
    int n_divisions = 1000;  // For integration
    int n_bins = 50;         // For histogramming data

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 1: Normal Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // Try Normal distribution with different parameters
        double mean = 0.0;
        double sigma = 2.0;

        NormalDistribution normal(mean, sigma, range_min, range_max, "../Outputs/png/Normal_Test");

        // Calculate integral
        double integral = normal.integral(n_divisions);
        normal.printInfo();

        // Plot function with data
        normal.plotFunction();
        normal.plotData(mystery_data, n_bins, true);

        std::cout << "\nNormal distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 2: Cauchy-Lorentz Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // Try Cauchy-Lorentz distribution
        double x0 = 0.0;
        double gamma = 1.0;

        CauchyLorentzDistribution cauchy(x0, gamma, range_min, range_max, "../Outputs/png/CauchyLorentz_Test");

        double integral = cauchy.integral(n_divisions);
        cauchy.printInfo();

        cauchy.plotFunction();
        cauchy.plotData(mystery_data, n_bins, true);

        std::cout << "\nCauchy-Lorentz distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 3: Crystal Ball Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // Try Crystal Ball distribution (common in particle physics!)
        double mean = 0.0;
        double sigma = 1.5;
        double alpha = 1.5;
        double n = 2.0;

        CrystalBallDistribution crystal(mean, sigma, alpha, n, range_min, range_max,
                                       "../Outputs/png/CrystalBall_Test");

        double integral = crystal.integral(n_divisions);
        crystal.printInfo();

        crystal.plotFunction();
        crystal.plotData(mystery_data, n_bins, true);

        std::cout << "\nCrystal Ball distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Best Fit: Cauchy-Lorentz Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        // After visual inspection, Cauchy-Lorentz seems to fit best
        // Fine-tune parameters
        double x0 = 0.0;
        double gamma = 1.0;

        CauchyLorentzDistribution best_fit(x0, gamma, range_min, range_max,
                                          "../Outputs/png/BestFit_CauchyLorentz");

        double integral = best_fit.integral(n_divisions);
        best_fit.printInfo();

        best_fit.plotFunction();
        best_fit.plotData(mystery_data, n_bins, true);

        std::cout << "\n--- Sampling from best fit distribution ---" << std::endl;
        int n_samples = 10000;
        double proposal_width = 1.5;  // Tuned for good acceptance rate

        std::cout << "Generating " << n_samples << " samples using Metropolis algorithm..." << std::endl;
        std::vector<double> sampled_data = best_fit.metropolisSample(n_samples, proposal_width);

        std::cout << "Sampled " << sampled_data.size() << " points!" << std::endl;

        // Create plot with function, mystery data, and sampled data
        best_fit.plotData(sampled_data, n_bins, false);  // false = sampled data (blue)

        std::cout << "\nFinal plot with sampled data saved!" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "All tests complete!" << std::endl;
    std::cout << "Check Outputs/png/ for plots" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
