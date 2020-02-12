/// @file run.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Run result
/// @version 0.1
/// @date 2020-02-05

#ifndef run_h
#define run_h

#include <stdio.h>
#include <vector>
#include "data_stats.h"

using namespace std;

/// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
void setSeed();

/// Run genetic algorithm for a certain function
DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &),float max, float min);

/// Write output file for record
void output(string func_name, DataStats result, vector<vector<float>> f_best_history);

/// Write output file for all function results
void output_all(vector<DataStats> result_best);

#endif /* run_hpp */
