#include "whale.h"
#include "population.h"
#include "../lib/mt64.h"
#include <iostream>
#include <cmath>

using namespace std;
WOA::WOA(float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_high = u;
    population.init(psize, dimension, f, l, u);
}

vector<float> WOA::run(){
    population.reset();
    vector<float> global_best_history;

    for (int g = 0; g < gmax; g++){
        float a = 2.0 * (gmax  -g)/ gmax;
        for (int i = 0; i < psize; i++){
            float p = genrand64_real1();
            float particle_rand = int(genrand64_real1() * psize);
            float l = -1 + genrand64_real1() * 2;

            for (int j = 0; j < dimension; j++) {
                if (p < 0.5) {
                    float r = genrand64_real1();
                    float a_ = 2.0 * a * r - a;
                    float c = 2.0 * r;
                    float d;

                    if (fabs(a_) < 1) {
                        d = fabs(c * population.data_best[j] - population.data[i][j]);
                        population.data[i][j] = population.data_best[j] - a_ * d;
                    } else {
                        d = fabs(c * population.data[particle_rand][j] - population.data[i][j]);
                        population.data[i][j] -= a_ * d;
                    }
                } else {
                    float d = fabs(population.data_best[j] - population.data[i][j]);
                    population.data[i][j] = d * pow(M_E, b * l) * cos( 2.0 * M_PI * l) +  population.data[i][j];
                }
                /// check solution bound
                if (population.data[i][j] < bound_low){
                    population.data[i][j] = bound_low;
                } else if (population.data[i][j] > bound_high){
                    population.data[i][j] = bound_high;
                }
            }

            /// get fitness
            population.cost[i] = function(population.data[i]);

            /// update global best
            if (population.cost[i] < population.cost_best){
                population.data_best = population.data[i];
                population.cost_best = population.cost[i];
            }
        }
        global_best_history.push_back(population.cost_best);
    }
    return global_best_history;
}