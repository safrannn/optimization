/// @file differential_evolution.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief differential evolution algorithm
/// @version 1.0
/// @date 2020-02-11

#ifndef differential_evolution_h
#define differential_evolution_h
#include <string>
#include <vector>
#include "population.h"

using namespace std;

struct DEStrategy{
    string perturbed_vector; /// x: string denoting the vector to be perturbed, choosing from best, rand or rand-to-best
    int difference_vector; /// y: number of difference vector considered for perturbation of x, 1 or 2
    string crossover_type; /// z: type of crossover being used, exponential or binomial
};

class DE{
public:
    DE(DEStrategy s, float (*f)(vector<float> &), float l, float u);
    vector<float> run();

private:
    int population_size = 200; /// Number of population
    int dimension = 30; /// Dimension
    float bound_low; ///Lower bound of the function
    float bound_up; ///Higher bound of the function
    int gmax= 100; /// Maximum number of generation
    float crossover_rate = 0.8; /// Crossover rate
    float scaling_factor1 = 0.5; /// Scaling factor (0-1.2]
    float scaling_factor2 = 0.5; /// Scaling factor (0-1.2]

    DEStrategy strategy;

    Population population; /// Population
    float (*function)(vector<float> &);

    vector<int> select_r(int count, int index);
    float formulation(int i, int j);
};

#endif //differential_evolution.h