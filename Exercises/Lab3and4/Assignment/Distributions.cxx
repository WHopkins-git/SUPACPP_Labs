// Distributions.cxx
// Implementation of custom distribution classes
// Date: 28th November 2025

#include "Distributions.h"
#include <cmath>
#include <iostream>
#include <random>

const double PI = 3.14159265358979323846;

// ========== Normal Distribution ==========

NormalDistribution::NormalDistribution(double mean, double sigma, double range_min,
                                       double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_mean(mean), m_sigma(sigma) {
    // m_FunctionName already set by parent constructor from outfile
}

NormalDistribution::~NormalDistribution() {}

double NormalDistribution::callFunction(double x) {
    // Gaussian: f(x) = (1 / (σ√(2π))) * exp(-(1/2)*((x-μ)/σ)²)
    double exponent = -0.5 * ((x - m_mean) / m_sigma) * ((x - m_mean) / m_sigma);
    return (1.0 / (m_sigma * sqrt(2.0 * PI))) * exp(exponent);
}

void NormalDistribution::printInfo() {
    std::cout << "\n=== Normal Distribution ===" << std::endl;
    std::cout << "Mean (μ): " << m_mean << std::endl;
    std::cout << "Std Dev (σ): " << m_sigma << std::endl;
    FiniteFunction::printInfo();
}

std::vector<double> NormalDistribution::metropolisSample(int n_samples, double proposal_width) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform(m_RMin, m_RMax);
    std::uniform_real_distribution<> uniform_01(0.0, 1.0);

    // Start with random point in range
    double x_current = uniform(gen);
    int accepted = 0;

    for (int i = 0; i < n_samples; i++) {
        // Propose new point from normal distribution centered at current point
        std::normal_distribution<> proposal(x_current, proposal_width);
        double x_proposed = proposal(gen);

        // Keep proposed point within range
        if (x_proposed < m_RMin || x_proposed > m_RMax) {
            samples.push_back(x_current);
            continue;
        }

        // Calculate acceptance ratio A = min(f(y)/f(x_i), 1)
        double f_current = this->callFunction(x_current);
        double f_proposed = this->callFunction(x_proposed);
        double acceptance = std::min(f_proposed / f_current, 1.0);

        // Accept or reject
        double random_uniform = uniform_01(gen);
        if (random_uniform < acceptance) {
            x_current = x_proposed;  // Accept
            accepted++;
        }
        // If rejected, x_current stays the same

        samples.push_back(x_current);
    }

    double acceptance_rate = 100.0 * accepted / n_samples;
    std::cout << "Acceptance rate: " << acceptance_rate << "%" << std::endl;

    return samples;
}

// ========== Cauchy-Lorentz Distribution ==========

CauchyLorentzDistribution::CauchyLorentzDistribution(double x0, double gamma,
                                                     double range_min, double range_max,
                                                     std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_x0(x0), m_gamma(gamma) {
    // m_FunctionName already set by parent constructor from outfile
}

CauchyLorentzDistribution::~CauchyLorentzDistribution() {}

double CauchyLorentzDistribution::callFunction(double x) {
    // Cauchy-Lorentz: f(x) = 1 / (πγ * [1 + ((x-x₀)/γ)²])
    double term = (x - m_x0) / m_gamma;
    return 1.0 / (PI * m_gamma * (1.0 + term * term));
}

void CauchyLorentzDistribution::printInfo() {
    std::cout << "\n=== Cauchy-Lorentz Distribution ===" << std::endl;
    std::cout << "Location (x₀): " << m_x0 << std::endl;
    std::cout << "Scale (γ): " << m_gamma << std::endl;
    FiniteFunction::printInfo();
}

std::vector<double> CauchyLorentzDistribution::metropolisSample(int n_samples, double proposal_width) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform(m_RMin, m_RMax);
    std::uniform_real_distribution<> uniform_01(0.0, 1.0);

    double x_current = uniform(gen);
    int accepted = 0;

    for (int i = 0; i < n_samples; i++) {
        std::normal_distribution<> proposal(x_current, proposal_width);
        double x_proposed = proposal(gen);

        if (x_proposed < m_RMin || x_proposed > m_RMax) {
            samples.push_back(x_current);
            continue;
        }

        double f_current = this->callFunction(x_current);
        double f_proposed = this->callFunction(x_proposed);
        double acceptance = std::min(f_proposed / f_current, 1.0);

        double random_uniform = uniform_01(gen);
        if (random_uniform < acceptance) {
            x_current = x_proposed;
            accepted++;
        }

        samples.push_back(x_current);
    }

    double acceptance_rate = 100.0 * accepted / n_samples;
    std::cout << "Acceptance rate: " << acceptance_rate << "%" << std::endl;

    return samples;
}

// ========== Crystal Ball Distribution ==========

CrystalBallDistribution::CrystalBallDistribution(double mean, double sigma, double alpha,
                                                 double n, double range_min, double range_max,
                                                 std::string outfile)
    : FiniteFunction(range_min, range_max, outfile),
      m_mean(mean), m_sigma(sigma), m_alpha(alpha), m_n(n) {
    // m_FunctionName already set by parent constructor from outfile
    computeConstants();
}

CrystalBallDistribution::~CrystalBallDistribution() {}

void CrystalBallDistribution::computeConstants() {
    // Pre-compute the constants A, B, C, D, N for efficiency
    double abs_alpha = fabs(m_alpha);

    // A = (n/|α|)^n * exp(-|α|²/2)
    m_A = pow(m_n / abs_alpha, m_n) * exp(-abs_alpha * abs_alpha / 2.0);

    // B = n/|α| - |α|
    m_B = m_n / abs_alpha - abs_alpha;

    // C = (n/|α|) * (1/(n-1)) * exp(-|α|²/2)
    m_C = (m_n / abs_alpha) * (1.0 / (m_n - 1.0)) * exp(-abs_alpha * abs_alpha / 2.0);

    // D = sqrt(π/2) * (1 + erf(|α|/√2))
    m_D = sqrt(PI / 2.0) * (1.0 + erf(abs_alpha / sqrt(2.0)));

    // N = 1 / (σ(C + D))
    m_N = 1.0 / (m_sigma * (m_C + m_D));
}

double CrystalBallDistribution::callFunction(double x) {
    // Standardized variable
    double t = (x - m_mean) / m_sigma;

    // Crystal Ball function has two regions:
    // Gaussian core for t > -α
    // Power law tail for t ≤ -α

    if (t > -m_alpha) {
        // Gaussian part: exp(-(x-x̄)²/(2σ²))
        return m_N * exp(-t * t / 2.0);
    } else {
        // Power law tail: A * (B - t)^(-n)
        return m_N * m_A * pow(m_B - t, -m_n);
    }
}

void CrystalBallDistribution::printInfo() {
    std::cout << "\n=== Crystal Ball Distribution ===" << std::endl;
    std::cout << "Mean (x̄): " << m_mean << std::endl;
    std::cout << "Sigma (σ): " << m_sigma << std::endl;
    std::cout << "Alpha (α): " << m_alpha << std::endl;
    std::cout << "n: " << m_n << std::endl;
    std::cout << "Computed constants:" << std::endl;
    std::cout << "  A = " << m_A << std::endl;
    std::cout << "  B = " << m_B << std::endl;
    std::cout << "  N = " << m_N << std::endl;
    FiniteFunction::printInfo();
}

std::vector<double> CrystalBallDistribution::metropolisSample(int n_samples, double proposal_width) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform(m_RMin, m_RMax);
    std::uniform_real_distribution<> uniform_01(0.0, 1.0);

    double x_current = uniform(gen);
    int accepted = 0;

    for (int i = 0; i < n_samples; i++) {
        std::normal_distribution<> proposal(x_current, proposal_width);
        double x_proposed = proposal(gen);

        if (x_proposed < m_RMin || x_proposed > m_RMax) {
            samples.push_back(x_current);
            continue;
        }

        double f_current = this->callFunction(x_current);
        double f_proposed = this->callFunction(x_proposed);
        double acceptance = std::min(f_proposed / f_current, 1.0);

        double random_uniform = uniform_01(gen);
        if (random_uniform < acceptance) {
            x_current = x_proposed;
            accepted++;
        }

        samples.push_back(x_current);
    }

    double acceptance_rate = 100.0 * accepted / n_samples;
    std::cout << "Acceptance rate: " << acceptance_rate << "%" << std::endl;

    return samples;
}
