#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "func.h"
#include "whale.h"
#include "data_stats.h"
#include "../lib/mt64.h"

using namespace std;

/// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
void setSeed(){
    init_genrand64((uint64_t)time(nullptr));
}

/// run pso for a function
/// @param strat strategy
/// @param experiment number of experiment
/// @param f function
/// @param l low x bound
/// @param u up x bound
/// @return return result analysis
DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &), float l, float u){
    DataStats result;
    vector<vector<float>> f_bests_history;
    float time_temp = 0;

    WOA woa(f, l, u);
    for (int i = 0; i < experiment; i++){
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        vector<float> f_best_history = woa.run();
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
        float f_best = f_best_history[f_best_history.size()-1];
        result.data.push_back(f_best);
        f_bests_history.push_back(f_best_history);

        time_temp = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
        result.time.push_back(time_temp);
    }
    result.run();
    output_func(func_name,result,f_bests_history);
    cout << "done: " << func_name << endl;
    return result;
}

/// write result to a file for one function
/// @param func_name function name
/// @param result result stat
/// @param f_bests_history cost history
void output_func(string func_name, DataStats result, vector<vector<float>> f_bests_history){
    /// output result stats
    ofstream file("out/" + func_name + "_stats.csv");
    file << "Mean,Median,Std,Range(low),Range(high),Time(mus)" << endl;
    file << result.mean << "," ;
    file << result.median << "," ;
    file << result.stand << "," ;
    file << result.range[0] << ",";
    file << result.range[1] << "," ;
    file << result.time_avg << endl;
    file.close();

    /// output time history
    ofstream file_timeHistory("out/"+ func_name + "_timeHistory.csv");
    for (int i = 0; i < result.time.size(); i++){
        if ( i == f_bests_history.size() - 1){
            file_timeHistory << result.time[i] << endl;
        }else{
            file_timeHistory << result.time[i] << ",";
        }
    }
    file_timeHistory.close();

    /// output f history
    ofstream file_fHistory("out/" + func_name + "_fHistory.csv");
    for (int i = 0; i < f_bests_history.size(); i++){
        for (int j = 0; j < f_bests_history[i].size(); j++) {
            if (j == f_bests_history[i].size() - 1) {
                file_fHistory << f_bests_history[i][j] << endl;
            } else {
                file_fHistory << f_bests_history[i][j] << ",";
            }
        }
    }
    file_fHistory.close();
}
/// write best result for every function
/// @param result_best best result for each function
void output_all(vector<DataStats> result_bests){
    ofstream file("out/woa_best_stats.csv");
    file << "Function,Mean,Median,Std,Range(low),Range(high),Time(mus)" << endl;
    for (int i = 0; i < result_bests.size(); i++){
        file << i + 1 << ",";
        file << result_bests[i].mean << "," ;
        file << result_bests[i].median << ",";
        file << result_bests[i].stand << "," ;
        file << result_bests[i].range[0] << ",";
        file << result_bests[i].range[1] << ",";
        file << result_bests[i].time_avg << endl;
    }
    file.close();
}