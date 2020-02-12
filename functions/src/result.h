/// \file

/// @file result.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Generate math function result
/// @version 0.1
/// @date 2020-02-01

#ifndef result_h
#define result_h

#include <stdio.h>
#include "func.h"
#include "util.h"

#include <vector>

using namespace std;

/// Generate solution for function in dimension of DIMENSION
vector<Runner> runOne(float (*functn)(vector<float> &), int min, int max);

/// print solution, fx and results
void printAll(vector<vector<Runner>> results);

/// Run all the 18 functions from func.h
void runAll();

#endif

// =========================
// End of result.h
// =========================
