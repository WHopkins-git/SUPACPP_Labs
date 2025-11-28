# Assignment 1 - Data Analysis Tool

## Overview
This program reads (x,y) coordinate data from a file and performs various statistical analyses including:
- Printing data points
- Calculating vector magnitudes
- Fitting straight lines using least squares
- Computing power functions recursively

## Files Included
- `AnalyseData.cxx` - Main steering script with user interface
- `CustomFunctions.h` - Header file with function declarations
- `CustomFunctions.cxx` - Implementation of analysis functions
- `Makefile` - Compilation script

## How to Compile
Simply run:
```bash
make
```

To clean build files:
```bash
make clean
```

## How to Run
After compiling, execute:
```bash
./AnalyseData
```

The program will present a menu with the following options:
1. Print first N lines of data
2. Calculate magnitudes of all data points
3. Fit straight line using least squares
4. Calculate x^y for each data point
5. Exit program

## Data Files
The program reads from:
- `input2D_float.txt` - Contains (x,y) coordinate data
- `error2D_float.txt` - Contains error estimates for each data point

## Output Files
Results are saved to:
- `output_first_N_lines.txt` - First N lines of data
- `output_magnitudes.txt` - Magnitude calculations
- `output_fit_results.txt` - Least squares fit parameters and chi-squared
- `output_power_results.txt` - Power function results

## Notes
- The program handles edge cases (e.g., requesting more lines than available)
- Power calculations use recursion without built-in power functions
- Chi-squared analysis includes degrees of freedom correction
