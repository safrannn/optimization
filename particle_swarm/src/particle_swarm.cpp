#include "particle_swarm.h"
#include "population.h"
#include "../lib/mt64.h"
#include <iostream>
#include <cmath>

using namespace std;
PSO::PSO(float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_high = u;
    population.init(psize, dimension, f, l, u);
}

vector<float> PSO::run(){
    population.reset();
    vector<float> global_best_history;

    for (int t = 0; t < tmax; t++){
        for (int i = 0; i < psize; i++){
            for (int j = 0; j < dimension; j++){
                /// calculate new velocity
                population.velocity[i][j] = (1.1 - population.global_best_cost/population.particle_best_cost[i]) * population.velocity[i][j]
                        + c1 * genrand64_real2() * (population.particle_best_data[i][j] - population.data[i][j])
                        + c2 * genrand64_real2() * (population.global_best_data[j] - population.data[i][j]);

                /// update particle value
                if (population.data[i][j] + population.velocity[i][j] > bound_high){
                    population.data[i][j] = bound_high;
                }else if (population.data[i][j] + population.velocity[i][j] < bound_low){
                    population.data[i][j] = bound_low;
                }else{
                    population.data[i][j] += population.velocity[i][j];
                }
            }
            /// calculate particle cost
            population.cost[i] = function(population.data[i]);
            /// check if the particle velocity has improved
            if (population.cost[i] < population.particle_best_cost[i]){
                population.particle_best_data[i] = population.data[i];
                population.particle_best_cost[i] = population.cost[i];
            }
            /// check if global best has improved
            if (population.cost[i] < population.global_best_cost){
                population.global_best_data = population.data[i];
                population.global_best_cost = population.cost[i];
            }
        }
        global_best_history.push_back(population.global_best_cost);
    }
    return global_best_history;
}