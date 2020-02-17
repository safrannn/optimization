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
    bound_low = l;
    bound_up = u;
    function = f;
}

/// reset the population for new run
void Population::reset(){
    data.clear();
    data.reserve(size);
    cost.clear();
    cost.reserve(size);
    cost_best = INT_MAX;
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    vector<float> indiv_data(dimension,0);
    float indiv_cost = 0;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            indiv_data[j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));
        }
        data.push_back(indiv_data);
        indiv_cost = function(indiv_data);
        cost.push_back(indiv_cost);

        if (indiv_cost <= cost_best){
            cost_best_index = i;
            cost_best = indiv_cost;
        }
    }
}








