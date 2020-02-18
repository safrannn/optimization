//#include <ctime>
//#include <cmath>
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include <string>
//
//#include "run.h"
//#include "func.h"
//#include "differential_evolution.h"
//#include "data_stats.h"
//#include "../lib/mt64.h"
//
//using namespace std;
//
///// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
//void setSeed(){
//    init_genrand64((uint64_t)time(nullptr));
//}
//
//
///// Run genetic algorithm for a certain function
///// @param experiment experiment size
///// @param func_name function name
///// @param min low bound for x
///// @param max high bound for x
///// @return best result among 10 strategies
//DataStats runFunc(int experiment, string func_name, float (*f)(vector<float> &),float l, float u){
//    vector<DataStats> results;
//    results.reserve(10);
//
//    /// strategy 1 best/1/exp
//    DEStrategy strategy1{"best", 1,"exponential"};
//    results.push_back(runStrategy(func_name, "strategy1",strategy1, experiment, f, l, u));
//    cout << "done: " << func_name  << " strategy 1" << endl;
//
//    DataStats result_best = results[0];
//    for (DataStats stat : results){
//        if (stat.median < result_best.median){
//            result_best = stat;
//        }
//    }
//    output_func(func_name,results);
//
//    cout << "done: " << func_name << endl;
//
//    return result_best;
//}
//
///// run one strategy for a function
///// @param strat strategy
///// @param experiment number of experiment
///// @param f function
///// @param l low x bound
///// @param u up x bound
///// @return return result analysis
//DataStats runStrategy(string func_name, string strategy_number, DEStrategy strat, int experiment, float (*f)(vector<float> &), float l, float u){
//    DE de(strat,f,l,u);
//
//    DataStats result;
//    vector<vector<float>> f_bests_history;
//    float time_temp = 0;
//
//    for (int i = 0; i < experiment; i++){
//        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
//        vector<float> f_best_history = de.run();
//        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
//        float f_best = f_best_history[f_best_history.size()-1];
//        result.data.push_back(f_best);
//        f_bests_history.push_back(f_best_history);
//
//        time_temp = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
//        result.time.push_back(time_temp);
//    }
//    result.run();
//    output_fHistory(func_name, strategy_number, f_bests_history);
//
//    return result;
//}
//
///// write result for one function for all strategies
///// @param func_name function name
///// @param result result of all strategies
//void output_func(string func_name, vector<DataStats> result){
//    ofstream file("out/" + func_name + "/" + func_name + "_stats.csv");
//    ofstream file_timeHistory("out/"+ func_name + "/"  + func_name + "_timeHistory.csv");
//    cout << "size" << result.size();
//    file << "Strategy,Mean,Median,Standard Deviation,Range,Time(mius)" << endl;
//    for (int i = 0; i < result.size(); i++){
//        file << std::to_string(i+1) << ",";
//        file << result[i+1].mean << "," ;
//        file << result[i+1].median << "," ;
//        file << result[i+1].stand << "," ;
//        file << result[i+1].range[0] << " - " << result[i].range[1] << "," ;
//        file << result[i+1].time_avg << endl;
//
//        for (int j = 0; j < result[i].time.size(); j++){
//            file_timeHistory << result[i].time[j] << ",";
//        }
//
//        file_timeHistory << endl;
//    }
//    file.close();
//    file_timeHistory.close();
//}
//
//void output_fHistory(string func_name, string strategy_number,vector<vector<float>> f_bests_history){
//    ofstream file_fHistory("out/" + func_name + "/" + func_name + "_" + strategy_number +"_fHistory.csv");
//    for (int i = 0; i < f_bests_history.size(); i++){
//        for (int j = 0; j < f_bests_history[i].size(); j++){
//            file_fHistory << f_bests_history[i][j] << ",";
//        }
//        file_fHistory << endl;
//    }
//    file_fHistory.close();
//}
//
///// write best result for every function
///// @param result_best best result for each function
//void output_all(vector<DataStats> result_bests){
//    ofstream file("out/de_best_stats.csv");
//    file << "Function,Mean,Median,Standard Deviation,Range,Time(mius)" << endl;
//    for (int i = 1; i <= result_bests.size(); i++){
//        file << i << ",";
//        file << result_bests[i].mean << "," ;
//        file << result_bests[i].median << ",";
//        file << result_bests[i].stand << "," ;
//        file << result_bests[i].range[0] << " - " << result_bests[i].range[1] << ",";
//        file << result_bests[i].time_avg << endl;
//    }
//    file.close();
//}