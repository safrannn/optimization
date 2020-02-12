#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "../lib/mt64.h"
#include "population.h"


Individual::Individual(float (*f)(vector<float> &), vector<float> numbers){
    function = f;
    data = numbers;

    cal_cost();
}

void Individual::cal_cost() {
    cost = function(data);
}


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

    reset();
    generate();
}

/// reset the population for new run
void Population::reset(){
    data.clear();
    data.reserve(size);
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    float cost_max = INT_MAX;
    for (int i = 0; i < size; i++){
        vector<float> x_temp;
        x_temp.reserve(dimension);
        for (int j = 0; j < dimension; j++){
            x_temp.push_back((float)(bound_low + (genrand64_real1()) * (bound_up - bound_low)));
        }
        Individual individual_new(function,x_temp);
        if (individual_new.cost < cost_max){
            individual_best = i;
        }
        data.push_back(individual_new);
    }
}