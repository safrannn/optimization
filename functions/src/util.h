/// @file util.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Utility functions and class for result analysis purpose
/// @version 0.1
/// @date 2020-02-01

#ifndef util_h
#define util_h

#include <stdio.h>
#include <vector>
#include <chrono>

using namespace std;

void setSeed();

/// Generate a population of pseudo-random number
void populationGen(vector<float> &pop, int d, int minBound, int maxBound);


/// Generate analytical results
class DataStats
{
public:
    float mean;
    float median;
    float stand;
    float range[2];
    
    void run(vector<float> &fx);
    
private:
    void analyzeMean(vector<float> &fx);
    void analyzeMedian(vector<float> &fx);
    void analyzeStand(vector<float> &fx);
    void analyzeRange(vector<float> &fx);
};


/// Generate pseudo-random population and function solution
class Runner{
public:
    vector<vector<float>> population;
    vector<float> fx;
    DataStats stats;
    float time;
    
    Runner(int d, float (*functn)(vector<float> &), int min, int max);
    void run();

private:
    int dimension;
    float (*f)(vector<float> &);
    int minBound;
    int maxBound;
    
    void getfx();
};

void printfx(string filename,vector<vector<Runner>> results);
void printResult(string filename,vector<vector<Runner>> results);

#endif

// =========================
// End of util.h
// =========================
