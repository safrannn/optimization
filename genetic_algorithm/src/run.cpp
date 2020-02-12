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
#include "../lib/mt64.h"
#include "data_stats.h"


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
DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &),float min, float max){
    DataStats result;
    vector<vector<float>> f_best_history;
    Genetic_algorithm function(f,min,max);
    
    for (int i = 0; i < experiment; i++){
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        function.run();
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
        
        result.data.push_back(function.f_best);
        f_best_history.push_back(function.f_best_history);
        result.time += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
    
    result.run();
    result.time /= experiment;
    output(func_name,result,f_best_history);
    return result;
}

/// Write output file for record
/// @param func_name function name
/// @param result result analysis data
/// @param f_best_history minimum value for fx
void output(string func_name, DataStats result, vector<vector<float>> f_best_history){
    ofstream file_stats("out/" + func_name + "_stats.csv");
    file_stats << "Mean,Median,Standard Deviation,Range,Time" << endl;
    file_stats << result.mean << "," ;
    file_stats << result.median << "," ;
    file_stats << result.stand << "," ;
    file_stats << result.range[0] << "-" << result.range[1] << "," ;
    file_stats << result.time << "ms" << endl;
    file_stats.close();

    ofstream file_result("out/" + func_name + "_result.csv");
    file_result << "Run#,Result" << endl;
    for (int i = 0; i < result.data.size(); i++){
        file_result << i+1 << "," << result.data[i]<< endl;
    }
    file_result.close();

    ofstream file_fHistory("out/" + func_name + "_fHistory.csv");
    file_fHistory << "Run#,f best" << endl;
    for (int i = 0; i < f_best_history.size(); i++){
        file_fHistory << i+1 << "," << "[";
        for (int j = 0; j < f_best_history[i].size(); j++){
            file_fHistory << f_best_history[i][j] << " ";
        }
        file_fHistory << "]" << endl;
    }
    file_fHistory.close();
}

/// Write output file for all function results
/// @param result_best statistics for results for every function
void output_all(vector<DataStats> result_best){
    ofstream file("out/ga_best_stats.csv");
    file << "Function,Mean,Median,Standard Deviation,Range,Time" << endl;
    for (int i = 1; i <= result_best.size(); i++){
        file << i << ",";
        file << result_best[i].mean << "," ;
        file << result_best[i].median << ",";
        file << result_best[i].stand << "," ;
        file << result_best[i].range[0] << "-" << result_best[i].range[1] ;
        file << "," << result_best[i].time << "ms" << endl;
    }
    file.close();
}