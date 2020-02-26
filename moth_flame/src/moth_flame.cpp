#include "moth_flame.h"
#include "population.h"
#include "../lib/mt64.h"
#include <iostream>
#include <cmath>

using namespace std;
MFO::MFO(float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_high = u;
    population.init(psize, dimension, f, l, u);
}

vector<float> MFO::run(){
    population.reset();
    vector<float> global_best_history;

    for (int g = 0; g < gmax; g++){
        /// update flame number using Eq. 3.14
        int flame_number = (int)(psize - (g + 1) * (psize - 1) / gmax);

        /// update r
        float r =  -1 + (-2 - -1) * ((g + 1) / gmax);

        /// get moth fitness, and sort moth and moth fitness according to moth fitness
        population.sort_moth();

        /// sort flame and sorted flame fitness according to moth fitness
        population.get_flame(flame_number);

        for (int i = 0; i < psize; i++){
            for (int j = 0; j < dimension; j++){
                /// update t
                float t = r + genrand64_real1() * (1 - r);

                /// calculate D using Eq. 3.13 and update M(i,j) using Eq. 3.11 and 3.12 with respect to the corresponding moth
                if (i < flame_number){
                    float d = fabs(population.flame[i][j] - population.moth[i][j]);
                    population.moth[i][j] = d * pow(M_E, t) * cos(2 * M_PI * t) + population.flame[i][j];
                }else{
                    float d = fabs(population.flame[flame_number - 1][j] - population.moth[i][j]);
                    population.moth[i][j] = d * pow(M_E, t) * cos(2 * M_PI * t) + population.flame[flame_number - 1][j];
                }
                /// bring moth back if goes beyond the bound
                if (population.moth[i][j] > bound_high){
                    population.moth[i][j] = bound_high;
                }else if (population.moth[i][j] < bound_low){
                    population.moth[i][j] = bound_low;
                }
            }
        }

        global_best_history.push_back(function(population.flame[0]));
    }

    return global_best_history;
}