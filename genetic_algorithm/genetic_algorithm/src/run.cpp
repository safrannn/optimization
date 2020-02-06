#include <stdint.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "func.h"
#include "genetic_algorithm.h"
#include "util.h"
#include "../lib/mt64.h"


using namespace std;

/// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
void setSeed(){
    init_genrand64((uint64_t)time(NULL));
}


/// Run genetic algorithm for a certain function
/// @param experiment experiment size
/// @param func_name function name
/// @param min low bound for x
/// @param max high bound for x
void runFunc(int experiment, string func_name, float (*f)(vector<float> &),int min, int max){
    DataStats result;
    vector<vector<float>> f_best_history;
    vector<vector<float>> best_solution;
    float time = 0.0;
    Genetic_algorithm function(f,min,max);
    
    for (int i = 0; i < experiment; i++){
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        function.run();
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
        
        result.data.push_back(function.f_best);
        f_best_history.push_back(function.f_best_history);
        best_solution.push_back(function.solution_best);
        time += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    result.run();
    time /= experiment;
    output(func_name,result,f_best_history,best_solution,time);
}


/// Write output file for record
/// @param func_name function name
/// @param result result analysis data
/// @param f_best_history minimum value for fx
/// @param solution solution set for minimum fx
/// @param time running time
void output(string func_name, DataStats result, vector<vector<float>> f_best_history, vector<vector<float>> solution, float time){
    ofstream file_stats("bin/" + func_name + "_stats.csv");
    file_stats << "Mean" << "," << "Median" << "," << "Standard Devation" << "," << "Range" << "," << "Time" << endl;
    file_stats << result.mean << "," << result.median << "," << result.stand << "," << result.range[0] << "-" << result.range[1] << "," << time << "ms" << endl;
    file_stats.close();
    
    ofstream file_result("bin/" + func_name + "_result.csv");
    file_result << "Run#" << "," << "Result" << "," << "Solution" << endl;
    for (int i = 0; i < result.data.size(); i++){
        file_result << i+1 << "," << result.data[i] << "," << "[";
        for (int j = 0; j < solution[i].size(); j++){
            file_result << solution[i][j] << " ";
        }
        file_result << "]" << endl;
    }
    file_result.close();
    
    ofstream file_fHistory("bin/" + func_name + "_fHistory.csv");
    file_fHistory << "Run#" << "," << "f best" << endl;
    for (int i = 0; i < f_best_history.size(); i++){
        file_fHistory << i+1 << "," << "[";
        for (int j = 0; j < f_best_history[i].size(); j++){
            file_fHistory << f_best_history[i][j] << " ";
        }
        file_fHistory << "]" << endl;
    }
    file_fHistory.close();
    
}
