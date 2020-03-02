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

    vector<float> temp(dimension,0);
    for (int i = 0; i < size; i++){
        data.push_back(temp);
        cost.push_back(0);
    }
    data_best = temp;
    cost_best = INT_MAX;
}

/// reset the population for new run
void Population::reset(){
    vector<float> temp(dimension,0);
    data_best = temp;
    cost_best = INT_MAX;
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            /// generate data
            data[i][j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));
        }
        /// calculate cost
        cost[i] = function(data[i]);

        if (cost[i] < cost_best){
            data_best = data[i];
            cost_best = cost[i];
        }
    }
}

void Population::get_best() {
    for (int i = 0; i < size; i++){
        if (cost[i] < cost_best){
            data_best = data[i];
            cost_best = cost[i];
        }
    }
}










