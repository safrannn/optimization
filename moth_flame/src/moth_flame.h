/// @file moth_fire.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Moth fire optimization algorithm
/// @version 1.0
/// @date 2020-02-25


#ifndef moth_fire
#define moth_fire

#include "population.h"
#include "data_stats.h"

using namespace std;

class MFO{
public:
    MFO(float (*f)(vector<float> &), float l, float u);
    vector<float> run();

private:
    int gmax = 2000; /// Max iteration
    int psize = 500; /// Size of population
    int dimension = 30; /// Dimension
    Population population;

    float (*function)(vector<float> &); /// Objective function
    float bound_low; /// Objective function solution low bound
    float bound_high; /// Objective function solution high bound
};
#endif //moth_fire
