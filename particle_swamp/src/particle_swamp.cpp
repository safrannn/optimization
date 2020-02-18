#include "particle_swamp.h"
#include "population.h"

using namespace std;
PS::PS(float (*f)(vector<float> &), float l, float u){
    function = f;
    bound_low = l;
    bound_up = u;

    population.init(pop_size, pop_dimension, f, u, l);
}

vector<float> PS::run(){
    population.reset();
    vector<float> global_best_history;

    for (int t = 0; t < tmax; t++){
        for (int j = 0; j < pop_dimension; j++){
            float velocity_temp = population.velocity[t];
            velocity_temp += c1 * (population.cost

        }
    }

}