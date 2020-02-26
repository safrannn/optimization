#include <string>
#include <vector>
#include <iostream>

#include "../lib/mt64.h"
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

    population.init(population_size, dimension, function, bound_low, bound_up);
}

/// select random index r
/// @param count number of indexes to be selected
/// @param index current index
vector<int> DE::select_r(int count, int index) {
    vector<int> r_values;
    for (int i = 0; i < count; i++){
        int tempNumber = (int)(genrand64_real2() * population_size);
        for (int j = 0; j < r_values.size(); j++){
            if (tempNumber == r_values[j] || tempNumber == index){
                tempNumber = (int)(genrand64_real2() * population_size);
                j = -1;
            }
        }
        r_values.push_back(tempNumber);
    }
    return r_values;
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
        result += population.data[population.cost_best_index][j];
        result += scaling_factor1 * (population.data[r_values[0]][j] - population.data[r_values[1]][j]);
    }else if (strategy.perturbed_vector == "rand" && strategy.difference_vector == 1) {
        r_values = select_r(3,i);
        result += population.data[r_values[2]][j];
        result += scaling_factor1 * (population.data[r_values[0]][j] - population.data[r_values[1]][j]);
    }else if (strategy.perturbed_vector == "rand-to-best" && strategy.difference_vector == 1) {
        r_values = select_r(2,i);
        result += population.data[i][j];
        result += scaling_factor2 * (population.data[population.cost_best_index][j] - population.data[i][j]) +scaling_factor1 * (population.data[r_values[0]][j] - population.data[r_values[1]][j]);
    }else if (strategy.perturbed_vector == "best" && strategy.difference_vector == 2) {
        r_values = select_r(4,i);
        result += population.data[population.cost_best_index][j];
        result += scaling_factor1 * (population.data[r_values[0]][j] + population.data[r_values[1]][j] - population.data[r_values[2]][j] - population.data[r_values[3]][j]);
    }else if (strategy.perturbed_vector == "rand" && strategy.difference_vector == 2) {
        r_values = select_r(5,i);
        result += population.data[r_values[4]][j];
        result += scaling_factor1 * (population.data[r_values[0]][j] + population.data[r_values[1]][j] - population.data[r_values[2]][j] - population.data[r_values[3]][j]);
    }
    if (result <= bound_low || result >= bound_up){
        result = formulation(i, j);
    }
    return result;
}

/// run differential evolution algorithm
/// @param i ith individual
/// @param j jth element in individual
/// @return history values of best function value achieved
vector<float> DE::run(){
    /// reset population
    population.reset();
    vector<float> f_best_history(gmax,0);

    for (int g = 0; g < gmax; g++){
        for (int i = 0; i < population_size; i++){
            // mutate and recombine
            vector<int> r_values = select_r(3, i);
            int j_rand = (int)(genrand64_real2() * dimension);

            vector<float> trial(dimension,0);
            if (strategy.crossover_type == "binomial" ){
                for (int j = 0; j < dimension; j++) {
                    if (genrand64_real1() < crossover_rate || j == j_rand) {
                        trial[j] = formulation(i, j);
                    } else {
                        trial[j] = population.data[i][j];
                    }
                }
            }else if (strategy.crossover_type == "exponential" ){
                int l = (int)(genrand64_real2() * dimension);
                int n = (int)(genrand64_real2() * dimension);
                vector<bool> j_values(dimension,false);

                for (int k = n; k < n+l; k++){
                    j_values[k % dimension] = true;
                }
                for (int j = 0; j < dimension; j++) {
                    if (j_values[j]){
                        trial[j] = formulation(i, j);
                    }else{
                        trial[j] = population.data[i][j];
                    }
                }
            }

            // select
            float trial_cost = function(trial);
            if (trial_cost <= population.cost[i]) {
                population.data[i] = trial;
                population.cost[i] = trial_cost;
                if (trial_cost <= population.cost_best) {
                    population.cost_best = trial_cost;
                    population.cost_best_index = i;
                }
            }
        }
        f_best_history[g] = population.cost_best;
    }
    return f_best_history;
}


