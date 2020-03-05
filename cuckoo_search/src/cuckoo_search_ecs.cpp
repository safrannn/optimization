#include "cuckoo_search_ecs.h"
#include "population.h"
#include "../lib/mt64.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

ECS::ECS(float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_high = u;

    population.init(psize, dimension, f, l, u);
}
void ECS::reset(){
    population.reset();
}

vector<float> ECS::run(){
    reset();
    mt19937 generator(genrand64_real1());
    vector<float> global_best_history;

    for (int g = 0; g < gmax; g++){
        /// get a cuckoo i randomly, generate a new cuckoo Fi and calculate cost
        int i_index = genrand64_real2() * psize;
        int trial_i_index = i_index;
        vector<float> trial_i_data = population.data[trial_i_index];
        float r1 = genrand64_real1();
        float r2 = genrand64_real1();
        for (int m = 0; m < dimension; m++){
            float sigma = (log(g) / g) * (trial_i_data[m] - population.data_best[m]);
            normal_distribution<double> distribution(population.data_best[m], sigma);
            trial_i_data[m] += distribution(generator) + r1 * population.data_best[m] - r2 * trial_i_data[m];

            if (trial_i_data[m] < bound_low){
                trial_i_data[m] = bound_low;
            }else if (trial_i_data[m] > bound_high){
                trial_i_data[m] = bound_high;
            }
        }
        float trial_i_cost = function(trial_i_data);

        /// choose a nest j among n randomly and get Fj's cost
        int j_index = genrand64_real2() * psize;
        float j_cost = population.cost[j_index];

        /// replace j with i if Fj < Fi
        if (trial_i_cost < j_cost){
            population.data[j_index] = trial_i_data;
            population.cost[j_index] = trial_i_cost;
            if (trial_i_cost < population.cost_best){
                population.data_best = trial_i_data;
                population.cost_best = trial_i_cost;
            }
        }

        /// Generate a new solution by greedy selection
        float r3 = genrand64_real1();
        int k_index = genrand64_real2() * psize;
        vector<float> k_data = population.data[k_index];
        vector<float> trial_v_data;
        for (int m = 0; m < dimension; m++){
            trial_v_data.push_back(population.data[i_index][m] + r3 * (population.data[i_index][m] - k_data[m]));
            if (trial_v_data[m] < bound_low){
                trial_v_data[m] = bound_low;
            }else if (trial_v_data[m] > bound_high){
                trial_v_data[m] = bound_high;
            }
        }
        float trial_v_cost = function(trial_v_data);
        float i_cost = population.cost[i_index];

        /// replace i with k if Fk < Fi
        if (trial_v_cost < i_cost){
            population.data[i_index] = trial_v_data;
            population.cost[i_index] = trial_v_cost;
            if (trial_i_cost < population.cost_best){
                population.data_best = trial_v_data;
                population.cost_best = trial_v_cost;
            }
        }

        /// abandon pa of n worse nests, keep the best solutions and build new ones
        int m_low = pa * psize;

        population.sort_cost();
        for (int m = psize - 1; m >= m_low; m--){
            int range_low;
            if (m_low > psize){
                range_low = psize - 1;
            }else{
                range_low = m_low;
            }
            int trial_k_index = range_low + genrand64_real2() * (psize - range_low);
            int trial_l_index =  range_low + genrand64_real2() * (psize - range_low);
            while (trial_l_index == trial_k_index){
                trial_l_index = range_low + genrand64_real2() * (psize - range_low);
            }
            for (int n = 0; n < dimension; n++){
                float e = genrand64_real2();
                if ((pa - e) > 0) {
                    population.data[m][n] += alpha0 * (population.data[trial_k_index][n] - population.data[trial_l_index][n]);
                }
            }
            population.cost[m] = function(population.data[m]);

            if (population.cost[m] < population.cost_best){
                population.cost_best = population.cost[m];
            }

        }
        global_best_history.push_back(population.cost_best);
    }
    return global_best_history;
}