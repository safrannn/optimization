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

/// Population for genetic algorithm.
class Population{
public:
    void init(int s, int d, float (*f)(vector<float> &), float l, float u); /// Initialize a population

    vector<vector<float>> data;
    vector<float> velocity;
    vector<float> fitness;
    vector<float> cost;
    float global_best_fitness;
    float global_best_cost;

    void reset(); /// Reset the population for new run

private:
    int size;
    int dimension;
    int bound_low;
    int bound_up;
    float (*function)(vector<float> &);

    void generate(); /// Generate random number to fill the population
    float get_fitness_one(float cost);
    void get_best_all();

};

#endif /* population_hpp */