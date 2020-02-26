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
        moth.push_back(temp);
        moth_fitness.push_back(0);
    }
}

/// reset the population for new run
void Population::reset(){
    generate();
}

/// Generate random number to fill the population
void Population::generate(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < dimension; j++){
            /// generate moth position
            moth[i][j] = (float)(bound_low + (genrand64_real1()) * (bound_up - bound_low));
        }
        /// calculate moth fitness
        moth_fitness[i] = function(moth[i]);
    }
}

/// helper function for pair sort
/// @param a to be sorted according to b
/// @param b sort a according to b
bool myComparison(const pair<vector<float>, float> &a, const pair<vector<float>, float> &b) {
    return a.second<b.second;
}

void Population::sort_moth(){
    long n = size;
    /// get moth fitness
    for (int i = 0; i < size; i++){
        moth_fitness[i] = function(moth[i]);
    }

    pair<vector<float>, float> pairt[n];
    for (int i = 0; i < n; i++){
        pairt[i].first = moth[i];
        pairt[i].second = moth_fitness[i];
    }

    sort(pairt,pairt + n, myComparison);

    for (int i = 0; i < n; i++){
        moth[i] = pairt[i].first;
        moth_fitness[i] = pairt[i].second;
    }
}

void Population::get_flame(int flame_number){
    flame.resize(flame_number);
    for (int i = 0; i < flame_number; i++){
        flame[i] = moth[i];
    }
}











