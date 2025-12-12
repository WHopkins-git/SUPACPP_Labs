// Distributions.h
// Custom distribution classes
// William Hopkins
// December 2024

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include "../FiniteFunctions.h"
#include <vector>
#include <random>

// Normal distribution
class NormalDistribution : public FiniteFunction {
public:
    NormalDistribution(double mean, double sigma, double range_min, double range_max, std::string outfile);
    ~NormalDistribution();

    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> metropolisSample(int n_samples, double proposal_width = 1.0);

private:
    double m_mean;    // μ parameter
    double m_sigma;   // σ parameter
};

// Cauchy-Lorentz distribution
class CauchyLorentzDistribution : public FiniteFunction {
public:
    CauchyLorentzDistribution(double x0, double gamma, double range_min, double range_max, std::string outfile);
    ~CauchyLorentzDistribution();

    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> metropolisSample(int n_samples, double proposal_width = 1.0);

private:
    double m_x0;      // x₀ location parameter
    double m_gamma;   // γ scale parameter
};

// Crystal Ball distribution (used in particle physics!)
class CrystalBallDistribution : public FiniteFunction {
public:
    CrystalBallDistribution(double mean, double sigma, double alpha, double n,
                           double range_min, double range_max, std::string outfile);
    ~CrystalBallDistribution();

    double callFunction(double x) override;
    void printInfo() override;
    std::vector<double> metropolisSample(int n_samples, double proposal_width = 1.0);

private:
    double m_mean;    // x̄ parameter
    double m_sigma;   // σ parameter
    double m_alpha;   // α parameter (tail transition point)
    double m_n;       // n parameter (power law exponent)

    // Pre-computed constants for efficiency
    double m_A;
    double m_B;
    double m_C;
    double m_D;
    double m_N;

    void computeConstants();  // Calculate A, B, C, D, N
};

#endif
