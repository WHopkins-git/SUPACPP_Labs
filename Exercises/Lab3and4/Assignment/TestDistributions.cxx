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

    // Create Plots directory if it doesn't exist
    if (!std::filesystem::exists("Plots")) {
        std::filesystem::create_directories("Plots");
    }

    // Specify the mystery data file to use
    std::string datafile = "../../../Data/MysteryData20000.txt";
    std::vector<double> mystery_data = readMysteryData(datafile);

    if (mystery_data.empty()) {
        std::cerr << "No data loaded. Exiting." << std::endl;
        return 1;
    }

    // Define range and parameters
    double range_min = -10.0;
    double range_max = 10.0;
    int n_divisions = 1000;
    int n_bins = 50;

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 1: Normal Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        double mean = 0.0;
        double sigma = 2.0;

        NormalDistribution normal(mean, sigma, range_min, range_max, "Normal_Test");
        normal.integral(n_divisions);
        normal.printInfo();

        normal.plotFunction();
        normal.plotData(mystery_data, n_bins, true);

        std::cout << "\nNormal distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 2: Cauchy-Lorentz Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        double x0 = -2.0;
        double gamma = 0.82;

        CauchyLorentzDistribution cauchy(x0, gamma, range_min, range_max, "CauchyLorentz_Test");
        cauchy.integral(n_divisions);
        cauchy.printInfo();

        cauchy.plotFunction();
        cauchy.plotData(mystery_data, n_bins, true);

        std::cout << "\nCauchy-Lorentz distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Testing 3: Crystal Ball Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        double mean = -2.0;
        double sigma = 1.0;
        double alpha = 80.0;
        double n = 2.5;

        CrystalBallDistribution crystal(mean, sigma, alpha, n, range_min, range_max,
                                       "CrystalBall_Test");
        crystal.integral(n_divisions);
        crystal.printInfo();

        crystal.plotFunction();
        crystal.plotData(mystery_data, n_bins, true);

        std::cout << "\nCrystal Ball distribution plot saved!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << "Best Fit: Crystal Ball Distribution" << std::endl;
    std::cout << "==================================================" << std::endl;
    {
        double mean = -2.0;
        double sigma = 1.0;
        double alpha = 80.0;
        double n = 2.5;

        CrystalBallDistribution best_fit(mean, sigma, alpha, n, range_min, range_max,
                                        "BestFit_CrystalBall");
        best_fit.integral(n_divisions);
        best_fit.printInfo();

        best_fit.plotFunction();
        best_fit.plotData(mystery_data, n_bins, true);

        std::cout << "\n--- Sampling from best fit distribution ---" << std::endl;
        int n_samples = 10000;
        double proposal_width = 1.5;

        std::cout << "Generating " << n_samples << " samples using Metropolis algorithm..." << std::endl;
        std::vector<double> sampled_data = best_fit.metropolisSample(n_samples, proposal_width);

        std::cout << "Sampled " << sampled_data.size() << " points!" << std::endl;

        best_fit.plotData(sampled_data, n_bins, false);

        std::cout << "\nFinal plot with sampled data saved!" << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "All tests complete!" << std::endl;
    std::cout << "Check Plots/ for plots" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
