#include "cuckoo_search_gaussian.h"
#include "population.h"
#include "../lib/mt64.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

CSG::CSG(int strat, float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_high = u;
    strategy = strat;

    population.init(psize, dimension, f, l, u);
}
void CSG::reset(){
    population.reset();
}

vector<float> CSG::run(){
    reset();
    vector<float> global_best_history;

    for (int g = 0; g < gmax; g++){
        /// get a cuckoo i randomly, generate a new cuckoo Fi and calculate cost
        int trial_1_index = genrand64_real2() * psize;
        int trial_2_index = genrand64_real2() * psize;
        while (trial_1_index == trial_2_index){
            trial_2_index = genrand64_real2() * psize;
        }
        vector<float> trial_i_data = population.data[trial_1_index];
        for (int m = 0; m < dimension; m++){
            float alpha = alpha0 * (population.data[trial_2_index][m] - population.data[trial_1_index][m]);
            trial_i_data[m] += alpha * sigma0 * exp(-miu * g);
            if (trial_i_data[m] < bound_low){
                trial_i_data[m] = bound_low;
            }else if (trial_i_data[m] > bound_high){
                trial_i_data[m] = bound_high;
            }
        }
        float trial_i_cost = function(trial_i_data);

        /// choose a nest j among n randomly and get Fj's cost
        int trial_j_index = genrand64_real2() * psize;
        float trial_j_cost = population.cost[trial_j_index];

        /// replace j with i if Fj < Fi
        if (trial_i_cost < trial_j_cost){
            population.data[trial_j_index] = trial_i_data;
            population.cost[trial_j_index] = trial_i_cost;
            if (trial_i_cost < population.cost_best){
                population.cost_best = trial_i_cost;
            }
        }

        /// abandon pa of n worse nests, keep the best solutions and build new ones
        if (strategy == 1){
            pa = pa_max * g / gmax;
        }else if (strategy == 2){
            pa = pa_max * 0.6 * (exp((float)g / (float)gmax) - exp(0));
        }else if (strategy == 3){
            pa = pa_max * g * g * g/ (gmax * gmax * gmax);
        }else{
            pa = 0.25;
        }

        int m_low = pa * psize;

        population.sort_cost();
        for (int m = psize - 1; m >= m_low; m--){
            float e = genrand64_real2();
            if ((pa - e) > 0){
                int range_low;
                if (m_low > psize){
                    range_low = psize;
                }else{
                    range_low = m_low;
                }
                int trial_k_index = range_low + genrand64_real2() * (psize - range_low);
                int trial_l_index =  range_low + genrand64_real2() * (psize - range_low);
                while (trial_l_index == trial_k_index){
                    trial_l_index = range_low + genrand64_real2() * (psize - range_low);
                }
                for (int n = 0; n < dimension; n++){
                    population.data[m][n] += alpha0 * (population.data[trial_k_index][n] - population.data[trial_l_index][n]);
                }
                population.cost[m] = function(population.data[m]);

                if (population.cost[m] < population.cost_best){
                    population.cost_best = population.cost[m];
                }
            }
        }
        global_best_history.push_back(population.cost_best);
    }
    return global_best_history;
}