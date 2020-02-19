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
    Genetic_algorithm function(f,min,max);

    DataStats result;
    vector<vector<float>> f_best_history;
    float time = 0;
    
    for (int i = 0; i < experiment; i++){
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        function.run();
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
        
        result.data.push_back(function.f_best);
        f_best_history.push_back(function.f_best_history);

        time = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
        result.time.push_back(time);
        result.time_avg += time;
    }
    result.time_avg /= experiment;
    result.run();
    output(func_name,result,f_best_history);
    cout << "done: " << func_name << endl;
    return result;
}

/// Write output file for record
/// @param func_name function name
/// @param result result analysis data
/// @param f_best_history minimum value for fx
void output(string func_name, DataStats result, vector<vector<float>> f_best_history){
    ofstream file_stats("out/" + func_name + "_stats.csv");
    file_stats << "Strategy,Mean,Median,Std,Range(low),Range(high),Average time(mus)" << endl;
    file_stats << "GA," ;
    file_stats << result.mean << "," ;
    file_stats << result.median << "," ;
    file_stats << result.stand << "," ;
    file_stats << result.range_low << ",";
    file_stats << result.range_high << "," ;
    file_stats << result.time_avg << endl;
    file_stats.close();

    ofstream file_fBest("out/" + func_name + "_fBest.csv");
    for (int i = 0; i < result.data.size(); i++){
        file_fBest << result.data[i]<< endl;
    }
    file_fBest.close();

    ofstream file_time("out/" + func_name + "_timeHistory.csv");
    for (int i = 0; i < result.time.size(); i++){
        file_time << result.time[i]<< endl;
    }
    file_time.close();

    ofstream file_fHistory("out/" + func_name + "_fHistory.csv");
    for (int i = 0; i < f_best_history.size(); i++){
        for (int j = 0; j < f_best_history[i].size(); j++){
            if (j == f_best_history[i].size() - 1){
                file_fHistory << f_best_history[i][j];
            }else {
                file_fHistory << f_best_history[i][j] << ",";
            }
        }
        file_fHistory << endl;
    }
    file_fHistory.close();
}

/// Write output file for all function results
/// @param result_best statistics for results for every function
void output_all(vector<DataStats> result_best){
    ofstream file("out/ga_best_stats.csv");
    file << "f,Mean,Median,Std,Range(low),Range(high),Time(mus)" << endl;
    for (int i = 0; i < result_best.size(); i++){
        file << std::to_string(i + 1) << ",";
        file << result_best[i].mean << "," ;
        file << result_best[i].median << ",";
        file << result_best[i].stand << "," ;
        file << result_best[i].range_low << ",";
        file << result_best[i].range_high << "," ;
        file << result_best[i].time_avg << endl;
    }
    file.close();
}