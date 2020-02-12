/// @file population.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Population generation
/// @version 1.0
/// @date 2020-02-1

#ifndef population_h
#define population_h

#include <stdio.h>
#include <vector>

using namespace std;

/// Individual for population
class Individual{
public:
    Individual(float (*f)(vector<float> &), vector<float> numbers);
    vector<float> data;
    float (*function)(vector<float> &);

    float cost;

private:
    void cal_cost();
};

/// Population for genetic algorithm.
class Population{
public:
    void init(int s, int d, float (*f)(vector<float> &), float l, float u); /// Initialize a population

    vector<Individual> data;
    int individual_best;

    void reset(); /// Reset the population for new run

private:
    int size;
    int dimension;
    int bound_low;
    int bound_up;
    float (*function)(vector<float> &);

    void generate(); /// Generate random number to fill the population
};

#endif /* population_hpp */
