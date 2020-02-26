#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "cuckoo_search.h"
#include "data_stats.h"

using namespace std;

/// run pso for a function
/// @param strat strategy
/// @param experiment number of experiment
/// @param f function
/// @param l low x bound
/// @param u up x bound
/// @return return result analysis
DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &), float l, float u){
    vector<DataStats> results;
    DataStats result_best;
    float time_temp = 0;

    for (int strategy = 0; strategy < 4; strategy++){
        vector<vector<float>> f_bests_history;
        CS cs(strategy,f, l, u);
        DataStats result;
        for (int i = 0; i < experiment; i++){
            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
            vector<float> f_best_history = cs.run();
            chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
            f_bests_history.push_back(f_best_history);

            float f_best = f_best_history[f_best_history.size()-1];
            result.data.push_back(f_best);

            time_temp = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
            result.time.push_back(time_temp);
        }
        result.run();
        results.push_back(result);

        if (result.mean < result_best.mean){
            result_best = result;
        }
        output_fHistory(strategy,func_name, f_bests_history);
        cout << "done: " << func_name << " - strategy: " << strategy << endl;
    }
    output_func(func_name, results);
    cout << "done: " << func_name << endl;
    return result_best;
}

void output_fHistory(int strategy, string func_name, vector<vector<float>> f_bests_history){
    /// output f history
    ofstream file_fHistory("out/" + func_name + "/" + func_name + "_strategy" + to_string(strategy) + "_fHistory.csv");
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

/// write result to a file for one function
/// @param func_name function name
/// @param result result stat
/// @param f_bests_history cost history
void output_func(string func_name, vector<DataStats> results){
    /// output result stats
    ofstream file("out/" + func_name + "/" + func_name + "_stats.csv");
    file << "Strategy, Mean,Median,Std,Range(low),Range(high),Time(mus)" << endl;
    /// output time history
    ofstream file_timeHistory("out/" + func_name + "/" + func_name  + "_timeHistory.csv");

    for (int i = 0; i < results.size(); i++){
        /// write result to file
        file << to_string(i) << "," ;
        file << results[i].mean << "," ;
        file << results[i].median << "," ;
        file << results[i].stand << "," ;
        file << results[i].range[0] << ",";
        file << results[i].range[1] << "," ;
        file << results[i].time_avg << endl;

        /// write time history to file
        for (int j = 0; j < results[i].time.size(); j++){
            if ( j == results[i].time.size() - 1){
                file_timeHistory << results[i].time[j] << endl;
            }else{
                file_timeHistory << results[i].time[j] << ",";
            }
        }
    }
    file.close();
    file_timeHistory.close();
}

/// write best result for every function
/// @param result_best best result for each function
void output_all(vector<DataStats> result_bests){
    ofstream file("out/cuckoo_search_best_stats.csv");
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