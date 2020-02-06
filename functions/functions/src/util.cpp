#include "util.h"
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "../lib/mt64.h"

using namespace std;

/// Dimension values
int dimension[] = {10, 20, 30};
int dimension_size = 3;

/// Generate repeat times pseudo-random solution
int repeat = 50;


/// Set seed for <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html">Mersenne Twister</a>
void setSeed(){
    init_genrand64((uint64_t)time(NULL));
}

/// Generate a population of pseudo-random number
/// @param pop population vector
/// @param d dimension number of random number
/// @param minBound minimum bound of random number
/// @param maxBound maximum bound of random number
void populationGen(vector<float> &pop, int d, int minBound, int maxBound){
    for (int i = 0; i < d; i++){
       float number = minBound + (float)genrand64_real1() * (maxBound - minBound);
        pop.push_back(number);
    }
}


/// Generate analytical results
/// @param fx fx data
void DataStats::run(vector<float> &fx)
{
    analyzeMean(fx);
    analyzeMedian(fx);
    analyzeStand(fx);
    analyzeRange(fx);
}

/// Get fx data mean
/// @param fx fx data
void DataStats::analyzeMean(vector<float> &fx)
{
    float sum = 0;
    for (int i = 0; i < fx.size(); i++)
    {
        sum += fx[i];
    }
    mean = sum / fx.size();
}

/// Get fx data median
/// @param fx fx data
void DataStats::analyzeMedian(vector<float> &fx)
{
    sort(fx.begin(), fx.end());
    median = (fx[fx.size() / 2 - 1] + fx[fx.size() / 2]) / 2;
}

/// Get fx data standard deviation
/// @param fx fx data
void DataStats::analyzeStand(vector<float> &fx)
{
    float variance = 0.0;
    for (int i = 0; i < fx.size(); i++)
    {   variance += pow(fx[i] - mean, 2);
    }
    variance /= fx.size();
    stand = sqrt(variance);
}

/// Get fx data range
/// @param fx fx data
void DataStats::analyzeRange(vector<float> &fx)
{
    float min = fx[0];
    float max = fx[1];
    for (int i = 0; i < fx.size(); i++){
        if (fx[i] < min){
            min = fx[i];
        }else{
            max = fx[i];
        }
    }
    range[0] = min;
    range[1] = max;
}


/// Runner class constructor
/// @param d dimension
/// @param min minimum bound of random number
/// @param max maximum bound of random number
Runner::Runner(int d, float (*functn)(vector<float> &), int min, int max)
{
    dimension = d;
    f = functn;
    minBound = min;
    maxBound = max;
}

/// Get fx
void Runner::getfx()
{
    for (int i = 0; i < repeat; i++)
    {
        vector<float> tempPopulation;
        populationGen(tempPopulation, dimension, minBound, maxBound);
        population.push_back(tempPopulation);
        
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        fx.push_back(f(tempPopulation));
        chrono::high_resolution_clock::time_point finish = chrono::high_resolution_clock::now();
        time += chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
}

/// Run runner that get fxs and generate analytical results
void Runner::run()
{
    getfx();
    stats.run(fx);
}

/// Print function value
/// @param filename filename for output
/// @param results results
void printfx(string filename,vector<vector<Runner>> results){
    std::ofstream file("bin/" + filename + ".csv");
    file << "Function" << "," << "Dimension" << "," << "f(x)" << endl;
    for (int i = 1; i <= 18; i++){
        for (int j = 0; j < dimension_size; j++){
            file << i << "," << dimension[j] << ",";
            for (int k = 0; k < repeat; k++){
                file << results[i][j].fx[k] <<  "," ;
            }
            file << endl;
        }
    }
    file.close();
}

/// Print analytical results
/// @param filename filename for output
/// @param results results
void printResult(string filename,vector<vector<Runner>> results){
    std::ofstream file("bin/" + filename + ".csv");
    file << "Function" << "," << "Dimension" << "," << "Mean" << "," << "Median" << "," << "Standard Devation" << "," << "Range" << "," << "Time" << endl;
    for (int i = 1; i <= 18; i++){
        for (int j = 0; j < dimension_size; j++){
            file << i << "," << dimension[j] << ",";
            file << results[i][j].stats.mean <<  "," ;
            file << results[i][j].stats.median <<  "," ;
            file << results[i][j].stats.stand <<  "," ;
            file << results[i][j].stats.range[0] << "-" << results[i][j].stats.range[1] << "," ;
            file << results[i][j].time <<  "ms" ;
            file << endl;
        }
    }
    file.close();
}



