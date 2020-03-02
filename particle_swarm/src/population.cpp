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
        velocity.push_back(temp);
        cost.push_back(0);
        particle_best_data.push_back(temp);
        particle_best_cost.push_back(0);
    }
    global_best_data = temp;
    global_best_cost = INT_MAX;
}

/// reset the population for new run
void Population::reset(){
    global_best_cost = INT_MAX;
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            /// generate data
            data[i][j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));
            particle_best_data[i][j] = data[i][j];
            /// generate velocity
            velocity[i][j] = (float)((genrand64_real1()) * 0.5 * (bound_up - bound_low));
        }
        /// calculate cost
        cost[i] = function(data[i]);
        particle_best_cost[i] = cost[i];

        if (cost[i] < global_best_cost){
            global_best_cost = cost[i];
            global_best_data = data[i];
        }
    }
}










