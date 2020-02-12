#include <string>
#include <vector>
#include <iostream>

//#include "differential_evolution.h"
#include "../lib/mt64.h"
#include "population.h"
#include "differential_evolution.h"


using namespace std;

/// Initialize differential evolution algorithm to run for one function
/// @param f function
/// @param l low bound for x
/// @param u high bound for x
DE::DE(DEStrategy s, float (*f)(vector<float> &), float l, float u){
    strategy = {s.perturbed_vector,s.difference_vector,s.crossover_type};
    function = f;
    bound_low = l;
    bound_up = u;
}

/// select random index r
/// @param count number of indexes to be selected
/// @param index current index
vector<int> DE::select_r(int count, int index) {
    vector<int> result;
    for (int i = 0; i < count; i++){
        float tempNumber = (int)(genrand64_real2() * population_size);
        for (int i = 0; i < result.size();i++){
            if (tempNumber == result[i] || tempNumber == index){
                tempNumber = (int)(genrand64_real2() * population_size);
                i = -1;
            }
        }
        result.push_back(tempNumber);
    }
    return result;
}

/// generating trial individual
/// @param i ith individual
/// @param j jth element in individual
/// @return return jth element in trial individual
float DE::formulation(int i, int j){
    float result = 0.0;
    vector<int> r_values;
    if (strategy.perturbed_vector == "best" && strategy.difference_vector == 1){
        r_values = select_r(2,i);
        result += population.data[population.individual_best].data[j];
        result += scaling_factor1 * (population.data[r_values[0]].data[j] + population.data[r_values[1]].data[j]);
    }else if (strategy.perturbed_vector == "rand" && strategy.difference_vector == 1) {
        r_values = select_r(3,i);
        result += population.data[r_values[2]].data[j];
        result += scaling_factor1 * (population.data[r_values[0]].data[j] + population.data[r_values[1]].data[j]);
    }else if (strategy.perturbed_vector == "rand-to-best" && strategy.difference_vector == 1) {
        r_values = select_r(2,i);
        result += population.data[i].data[j];
        result += scaling_factor2 * (population.data[population.individual_best].data[j] - population.data[i].data[j]) +scaling_factor1 * (population.data[r_values[0]].data[j] + population.data[r_values[1]].data[j]);
    }else if (strategy.perturbed_vector == "best" && strategy.difference_vector == 2) {
        r_values = select_r(4,i);
        result += population.data[population.individual_best].data[j];
        result += scaling_factor1 * (population.data[r_values[0]].data[j] + population.data[r_values[1]].data[j] - population.data[r_values[2]].data[j] - population.data[r_values[3]].data[j]);
    }else if (strategy.perturbed_vector == "rand" && strategy.difference_vector == 2) {
        r_values = select_r(5,i);
        result += population.data[r_values[4]].data[j];
        result += scaling_factor1 * (population.data[r_values[0]].data[j] + population.data[r_values[1]].data[j] - population.data[r_values[2]].data[j] - population.data[r_values[3]].data[j]);
    }
    return result;
}

/// run differential evolution algorithm
/// @param i ith individual
/// @param j jth element in individual
/// @return history values of best function value achieved
vector<float> DE::run(){
    // init population
    population.init(population_size, dimension, function, bound_low, bound_up);
    vector<float> f_best_history;
    for (int g = 0; g < gmax; g++){
        for (int i = 0; i < population_size; i++){
            // mutate and recombine
            vector<int> r_values = select_r(3, i);
            int j_rand = (int)(genrand64_real2() * dimension);

            vector<float> x_trial(dimension,0);

            if (strategy.crossover_type == "binomial" ){
                for (int j = 0; j < dimension; j++) {
                    if (genrand64_real1() < crossover_rate || j == j_rand) {
                        x_trial[j] = formulation(i, j);
                    } else {
                        x_trial[j] = population.data[i].data[j];
                    }
                }
            }else if (strategy.crossover_type == "exponential" ){
                int l = (int)(genrand64_real2() * dimension);
                int n = (int)(genrand64_real2() * dimension);
                vector<int> j_values;
                j_values.reserve(l);
                for (int j = 0; j < dimension; j++) {
                    x_trial[j] = population.data[i].data[j];
                }
                for (int k = n; k < n+l; k++){
                    j_values.push_back(k % dimension);
                }
                for (int j : j_values) {
                    x_trial[j] = formulation(i, j);
                }
            }

            // select
            Individual individual_trial(function, x_trial);
            if (individual_trial.cost <= population.data[i].cost) {
                population.data[i] = individual_trial;
                if (individual_trial.cost <= population.data[population.individual_best].cost) {
                    population.individual_best = i;
                }
            }
        }
        f_best_history.push_back(population.data[population.individual_best].cost);
    }
    return f_best_history;
}


