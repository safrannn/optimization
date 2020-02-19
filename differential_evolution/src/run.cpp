#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "func.h"
#include "differential_evolution.h"
#include "data_stats.h"
#include "../lib/mt64.h"

using namespace std;

/// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
void setSeed(){
    init_genrand64((uint64_t)time(nullptr));
}

/// Run genetic algorithm for a certain function
/// @param experiment experiment size
/// @param func_name function name
/// @param min low bound for x
/// @param max high bound for x
/// @return best result among 10 strategies
DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &),float l, float u){
    vector<DataStats> results;
    results.reserve(10);

    /// strategy 1 best/1/exp
    DEStrategy strategy1{"best", 1,"exponential"};
    results.push_back(runStrategy(func_name, "strategy1",strategy1, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 1" << endl;

    /// strategy 2 rand/1/exp
    DEStrategy strategy2{"rand", 1,"exponential"};
    results.push_back(runStrategy(func_name, "strategy2", strategy2, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 2" << endl;

    /// strategy 3 rand-to-best/1/exp
    DEStrategy strategy3{"rand-to-best", 1,"exponential"};
    results.push_back(runStrategy(func_name, "strategy3", strategy3, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 3" << endl;

    /// strategy 4 best/2/exp
    DEStrategy strategy4{"best", 2,"exponential"};
    results.push_back(runStrategy(func_name, "strategy4", strategy4, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 4" << endl;

    /// strategy 5 rand/2/exp
    DEStrategy strategy5{"rand", 2,"exponential"};
    results.push_back(runStrategy(func_name, "strategy5", strategy5, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 5" << endl;

    /// strategy 6 best/1/bin
    DEStrategy strategy6{"best", 1,"binomial"};
    results.push_back(runStrategy(func_name, "strategy6", strategy6, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 6" << endl;

    /// strategy 7 rand/1/bin
    DEStrategy strategy7{"rand", 1,"binomial"};
    results.push_back(runStrategy(func_name, "strategy7", strategy7, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 7" << endl;

    /// strategy 8 rand-to-best/1/bin
    DEStrategy strategy8{"rand-to-best", 1,"binomial"};
    results.push_back(runStrategy(func_name, "strategy8", strategy8, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 8" << endl;

    /// strategy 9 best/2/bin
    DEStrategy strategy9{"best", 2,"binomial"};
    results.push_back(runStrategy(func_name, "strategy9", strategy9, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 9" << endl;

    /// strategy 10 rand/2/bin
    DEStrategy strategy10{"rand", 2,"binomial"};
    results.push_back(runStrategy(func_name, "strategy10", strategy10, experiment, f, l, u));
    cout << "done: " << func_name  << " strategy 10" << endl;

    DataStats result_best = results[0];
    for (DataStats stat : results){
        if (stat.median < result_best.median){
            result_best = stat;
        }
    }

    output_func(func_name,results);
    cout << "done: " << func_name << endl;
    return result_best;
}

/// run one strategy for a function
/// @param strat strategy
/// @param experiment number of experiment
/// @param f function
/// @param l low x bound
/// @param u up x bound
/// @return return result analysis
DataStats runStrategy(string func_name, string strategy_number, DEStrategy strat, int experiment, float (*f)(vector<float> &), float l, float u){
    DE de(strat,f,l,u);

    DataStats result;
    vector<vector<float>> f_bests_histories;
    float time_temp = 0;

    for (int i = 0; i < experiment; i++){
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        vector<float> f_bests_current = de.run();
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();

        result.data.push_back(f_bests_current[f_bests_current.size()-1]);
        f_bests_histories.push_back(f_bests_current);

        time_temp = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
        result.time.push_back(time_temp);
    }
    result.run();

    output_fHistory(func_name, strategy_number, f_bests_histories);

    return result;
}

/// write result for one function for all strategies
/// @param func_name function name
/// @param result result of all strategies
void output_func(string func_name, vector<DataStats> result){
    ofstream file("out/" + func_name + "/" + func_name + "_stats.csv");
    ofstream file_timeHistory("out/"+ func_name + "/"  + func_name + "_timeHistory.csv");

    file << "Strategy,Mean,Median,Std,Range(low),Range(high),Time(mius)" << endl;
    for (int i = 0; i < result.size(); i++){
        file << "DE" << std::to_string(i + 1) << ",";
        file << result[i].mean << "," ;
        file << result[i].median << "," ;
        file << result[i].stand << "," ;
        file << result[i].range_low << "," ;
        file << result[i].range_high << "," ;
        file << result[i].time_avg << endl;

        for (int j = 0; j < result[i].time.size(); j++){
            if (j == result[i].time.size() - 1){
                file_timeHistory << result[i].time[j];
            }else{
                file_timeHistory << result[i].time[j] << ",";
            }
        }
        file_timeHistory << endl;
    }
    file.close();
    file_timeHistory.close();
}

/// Write best result history for each strategy for each function
/// @param func_name function name
/// @param strategy_number strategy number
/// @param f_bests_history history of best function value achived
void output_fHistory(string func_name, string strategy_number,vector<vector<float>> f_bests_history){
    ofstream file_fHistory("out/" + func_name + "/" + func_name + "_" + strategy_number +"_fHistory.csv");
    for (int i = 0; i < f_bests_history.size(); i++){
        for (int j = 0; j < f_bests_history[i].size(); j++){
            if (j == f_bests_history[i].size() - 1){
                file_fHistory << f_bests_history[i][j];
            }else {
                file_fHistory << f_bests_history[i][j] << ",";
            }
        }
        file_fHistory << endl;
    }
    file_fHistory.close();
}

/// Write best result for every function
/// @param result_best best result for each function
void output_all(vector<DataStats> result_bests){
    ofstream file("out/de_best_stats.csv");
    file << "f,Mean,Median,Std,Range(low),Range(high),Time(mius)" << endl;
    for (int i = 0; i < result_bests.size(); i++){
        file << "de" << std::to_string(i + 1) << ",";
        file << result_bests[i].mean << "," ;
        file << result_bests[i].median << ",";
        file << result_bests[i].stand << "," ;
        file << result_bests[i].range_low << ",";
        file << result_bests[i].range_high << ",";
        file << result_bests[i].time_avg << endl;
    }
    file.close();
}