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

    velocity.clear();
    data.reserve(size);

    fitness.clear();
    data.reserve(size);

    cost.clear();
    data.reserve(size);

    global_best_fitness = INT_MAX;
    global_best_cost = INT_MAX;

    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    vector<float> data_temp(dimension,0);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            data_temp[j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));

        }
        data.push_back(data_temp);

        float cost_temp = function(data_temp);
        cost.push_back(cost_temp);
        float fitness_temp = get_fitness_one(cost_temp);
        fitness.push_back(fitness_temp);
        if (fitness_temp < global_best_fitness){
            global_best_fitness = fitness_temp;
            global_best_cost = cost_temp;
        }

        velocity[i] = (float)(0.5 * (genrand64_real1()) * (bound_up - bound_low));
    }
}

float Population::get_fitness_one(float cost) {
    if (cost > 0){
        return 1 / ( 1 + cost);
    }else{
        return 1 + fabs(cost);
    }
}











