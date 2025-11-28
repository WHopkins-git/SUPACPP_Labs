# Assignment 2 - Distribution Fitting and Sampling

## Overview
This program implements several statistical distribution classes that inherit from the `FiniteFunction` base class. The goal is to identify which distribution best matches mystery data and then sample from it using the Metropolis algorithm.

## Files Included
- `Distributions.h` - Header file for custom distribution classes
- `Distributions.cxx` - Implementation of Normal, Cauchy-Lorentz, and Crystal Ball distributions
- `TestDistributions.cxx` - Main test program
- `Makefile` - Build automation
- `README.md` - This file

## Implemented Distributions

### 1. Normal (Gaussian) Distribution
- Formula: f(x) = (1 / (σ√(2π))) × exp(-(1/2)×((x-μ)/σ)²)
- Parameters: mean (μ), standard deviation (σ)

### 2. Cauchy-Lorentz Distribution
- Formula: f(x) = 1 / (πγ × [1 + ((x-x₀)/γ)²])
- Parameters: location (x₀), scale (γ)

### 3. Crystal Ball Distribution
- Used in particle physics for detector resolution
- Combines Gaussian core with power-law tail
- Parameters: mean, sigma, alpha, n

## Features
- **Numerical Integration**: Fixed implementation using trapezoidal rule
- **Metropolis Sampling**: Generates pseudo-random samples from any distribution
- **Automatic Plotting**: Creates plots comparing functions with data
- **Parameter Tuning**: Easy to adjust distribution parameters

## How to Compile
```bash
make
```

## How to Run
```bash
./TestDistributions
```

or simply:
```bash
make run
```

## Output
Results are saved to `../Outputs/png/`:
- `Normal_Test.png` - Normal distribution vs. data
- `CauchyLorentz_Test.png` - Cauchy-Lorentz distribution vs. data
- `CrystalBall_Test.png` - Crystal Ball distribution vs. data
- `BestFit_CauchyLorentz.png` - Best fit with sampled data (blue points)

## Mystery Data Analysis
After testing all three distributions, the **Cauchy-Lorentz distribution** appears to best match the mystery data. This makes sense as the data shows heavy tails characteristic of the Cauchy distribution.

## Metropolis Algorithm
The sampling uses the Metropolis-Hastings algorithm:
1. Start at random point in range
2. Propose new point from normal distribution
3. Accept with probability min(f(y)/f(x), 1)
4. Repeat for desired number of samples

The proposal width can be tuned for better performance (currently set to 1.5 for good acceptance rate).

## Notes
- Integration uses 1000 divisions by default for good accuracy
- Data is binned into 50 bins for histogram visualization
- Range is set to [-10, 10] to encompass all data
