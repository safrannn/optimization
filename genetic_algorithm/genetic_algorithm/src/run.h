/// @file run.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Run result
/// @version 0.1
/// @date 2020-02-05

#ifndef run_h
#define run_h

#include <stdio.h>
#include <vector>
#include "util.h"

using namespace std;

void setSeed(); /// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>

void runFunc(int experiment, string func_name, float (*f)(vector<float> &),int max, int min); /// Run genetic algorithm for a certain function

void output(string func_name, DataStats result, vector<vector<float>> f_best_history, vector<vector<float>> solution, float time); /// Write output file for record


#endif /* run_hpp */
