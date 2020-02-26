/// @file population.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Population generation
/// @version 1.0
/// @date 2020-02-25

#ifndef population_h
#define population_h

#include <stdio.h>
#include <vector>

using namespace std;

/// Population for genetic algorithm.
class Population{
public:
    void init(int s, int d, float (*f)(vector<float> &), float l, float u); /// Initialize a population

    vector<vector<float>> moth;
    vector<float> moth_fitness;
    vector<vector<float>> flame;
//    vector<float> flame_fitness;

    void reset(); /// Reset the population for new run
    void sort_moth();
    void get_flame(int flame_number);

private:
    int size;
    int dimension;
    int bound_low;
    int bound_up;
    float (*function)(vector<float> &);

    void generate(); /// Generate random number to fill the population
};

#endif /* population_hpp */
