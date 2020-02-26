#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "../lib/mt64.h"
#include "population.h"

/// Initialize a population
/// @param s population size
/// @param d population dimension
/// @param low  x low bound
/// @param high x high bound
void Population::init(int s, int d, float (*f)(vector<float> &), float l, float u){
    size = s;
    dimension = d;
    function = f;
    bound_low = l;
    bound_up = u;
    cost_best = INT_MAX;

    vector<float> temp(dimension,0);
    for (int i = 0; i < size; i++){
        data.push_back(temp);
        cost.push_back(0);
    }
}

/// reset the population for new run
void Population::reset(){
    cost_best = INT_MAX;
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            /// generate position
            data[i][j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));
        }
        /// calculate cost
        cost[i] = function(data[i]);
        if (cost[i] < cost_best){
            cost_best = cost[i];
        }
    }
}

/// helper function for pair sort
/// @param a to be sorted according to b
/// @param b sort a according to b
bool myComparison(const pair<vector<float>,float> &a,const pair<vector<float>,float> &b)
{
    return a.second < b.second;
}

/// pair sort to sort the population by cost from low cost to high cost
void Population::sort_cost(){
    long n = size;

    pair<vector<float>, float> pairt[n];
    for (int i = 0; i < n; i++){
        pairt[i].first = data[i];
        pairt[i].second = cost[i];
    }

    sort(pairt,pairt + n,myComparison);

    for (int i = 0; i < n; i++){
        data[i] = pairt[i].first;
        cost[i] = pairt[i].second;
    }
}











