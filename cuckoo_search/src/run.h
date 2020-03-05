/// @file run.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief run
/// @version 1.0
/// @date 2020-02-11

#ifndef run_h
#define run_h

#include <vector>
#include "data_stats.h"
#include "cuckoo_search.h"

using namespace std;

void setSeed();

DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &), float l, float u);

void output_fHistory(string strategy, string func_name, vector<vector<float>> f_bests_history);

void output_func(string func_name, vector<DataStats> result);

void output_all(vector<DataStats> result_best);

#endif //run_h
