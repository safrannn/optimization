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
void Population::init(int s, int d, float (*funct)(vector<float> &), float l, float u){
    size = s;
    dimension = d;
    bound_low = l;
    bound_up = u;
    f = funct;
}

/// reset the population for new run
void Population::reset(){
    population.clear();
    population.reserve(size);
    cost.clear();
    cost.reserve(size);
    fitness.clear();
    fitness.reserve(size);
    fitness_total = 0;
}

/// Generate random number to fill the population
void Population::generation(){
    population.clear();
    for (int i = 0; i < size; i++){
        vector<float> newvect(dimension,0);
        population.push_back(newvect);
        for (int j = 0; j < dimension; j++){
            population[i][j] = bound_low + genrand64_real1() * (bound_up - bound_low);
        }
    }
}

/// Evaluate the population the population by first calculating each function's cost, then calculate fitness accordingly
void Population::evaluate(){
    cost.clear();
    fitness.clear();
    fitness_total = 0.0;

    for (vector<float> v : population){
        cost.push_back(f(v));
    }

    for (int s = 0; s < size; s++){
        float fit;
        if (cost[s] >= 0){
            fit = 1/(1 + cost[s]/10000);
        }else{
            fit = 1 + abs(cost[s]/10000);
        }
        fitness.push_back(fit);
        fitness_total += fit;
    }
}

/// helper function for pair sort
/// @param a to be sorted according to b
/// @param b sort a according to b
bool myComparison(const pair<vector<float>,float> &a,const pair<vector<float>,float> &b)
{
       return a.second<b.second;
}

/// pair sort to sort the population by cost
void Population::sort_by_cost(){
    long n = population.size();
    
    pair<vector<float>, float> pairt[n];
    for (int i = 0; i < n; i++){
        pairt[i].first = population[i];
        pairt[i].second = cost[i];
    }
  
    sort(pairt,pairt + n,myComparison);

    for (int i = 0; i < n; i++){
        population[i] = pairt[i].first;
        cost[i] = pairt[i].second;
    }
}

