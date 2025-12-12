# Assignment 2 - Distribution Fitting and Sampling
William Hopkins
December 2025

## Overview
This program implements several statistical distribution classes that inherit from the `FiniteFunction` base class. The goal is to identify which distribution best matches mystery data and then sample from it using the Metropolis algorithm.

## Files Included
- `Distributions.h` - Header file for custom distribution classes
- `Distributions.cxx` - Implementation of Normal, Cauchy-Lorentz, and Crystal Ball distributions
- `TestDistributions.cxx` - Main test program for distributions
- `TestDefaultFunction.cxx` - Test program for default FiniteFunction
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
- **Numerical Integration**: Trapezoidal rule for normalization
- **Metropolis Sampling**: Generates samples from any distribution with acceptance rate tracking
- **Automatic Plotting**: Creates plots comparing functions with data
- **Parameter Tuning**: Easy to adjust distribution parameters in code

## How to Compile
```bash
cd Assignment
make
```

This builds both `TestDistributions` and `TestDefaultFunction`.

## How to Run

### Test Default Function
```bash
./TestDefaultFunction
```
Tests the base FiniteFunction class with the invxsquared function f(x) = 1/(1+x²).

### Test Distributions
```bash
./TestDistributions
```
Tests all three distributions and performs Metropolis sampling on the best fit.

## Data Files
The programs use mystery data files from `../../../Data/`:
- TestDistributions uses `MysteryData20000.txt`
- TestDefaultFunction uses `MysteryData22012.txt`

## Output
Results are saved to `Plots/`:
- `DefaultFunction.png` - Default FiniteFunction test
- `NormalTest.png` - Normal distribution vs. data
- `CauchyLorentzTest.png` - Cauchy-Lorentz distribution vs. data
- `CrystalBallTest.png` - Crystal Ball distribution vs. data
- `BestFitNormal.png` - Best fit with sampled data (blue points)

## Mystery Data Analysis
After testing all three distributions, the **Normal distribution** with mean=-2.0 and sigma=1.0 best matches the mystery data.

## Metropolis Algorithm
The sampling uses the Metropolis-Hastings algorithm:
1. Start at random point in range
2. Propose new point from normal distribution (width = 1.5)
3. Accept with probability min(f(y)/f(x), 1)
4. Repeat for 10,000 samples

The algorithm prints the acceptance rate (typically ~58% for these parameters, which is optimal).

## Parameters Used
- **Normal**: mean = -2.0, sigma = 1.0
- **Cauchy-Lorentz**: x₀ = -2.0, γ = 0.82
- **Crystal Ball**: mean = -2.0, sigma = 1.0, alpha = 80.0, n = 2.5
- **Range**: [-10, 10]
- **Integration divisions**: 1000
- **Histogram bins**: 50

