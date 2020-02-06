/// @file population.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Population generation
/// @version 0.1
/// @date 2020-02-05

#ifndef population_h
#define population_h

#include <stdio.h>
#include <vector>

using namespace std;


/// Population for genetic algorithm.
/// Individual's population of x is represented by vector<float>.
class Population{
public:
    vector<vector<float>> population;
    vector<float> cost;
    vector<float> fitness;
    float fitness_total;
    
    void init(int s, int d, float (*funct)(vector<float> &), int low, int high); /// Initialize a population
    void generation(); /// Generate random number to fill the population
    void evaluate(); /// Evaluate the population the population by first calculating each function's cost, then calculate fitness accordingly
    void reset(); /// Reset the population for new run
    void sort_by_cost(); /// Pair sort to sort the population by cost
    
private:
    int size;
    int dimension;
    int bound_low;
    int bound_high;
    float (*f)(vector<float> &);
};

#endif /* population_hpp */
