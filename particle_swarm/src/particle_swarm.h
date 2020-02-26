/// @file particle_swamp.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Particle swarm optimization
/// @version 1.0
/// @date 2020-02-25


#ifndef particle_swamp
#define particle_swamp

#include "population.h"
#include "data_stats.h"

using namespace std;

class PSO{
public:
    PSO(float (*f)(vector<float> &), float l, float u);
    vector<float> run();

private:
    int tmax = 1000; /// Max iteration
    float c1 = 0.5;  /// Local optimal scaling factor
    float c2 = 2.0; /// Global optimal scaling facgor

    int psize = 500; /// Size of population
    int dimension = 30; /// Dimension
    Population population;

    float (*function)(vector<float> &); /// Objective function
    float bound_low; /// Objective function solution lower bound
    float bound_high; /// Objective function solution higher bound
};
#endif //particle_swamp
