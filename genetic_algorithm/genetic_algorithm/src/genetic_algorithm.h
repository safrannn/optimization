/// @file genetic_algorithm.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Genetic algorithm 
/// @version 0.1
/// @date 2020-02-05

#ifndef genetic_algorithm_h
#define genetic_algorithm_h

#include <stdio.h>
#include <vector>

#include "genetic_algorithm.h"
#include "population.h"

using namespace std;

class Genetic_algorithm{
public:
    float f_best = INT_MAX;
    vector<float> f_best_history; /// Minimum f value during execution
    vector<float> solution_best; /// Solution sets
    
    Genetic_algorithm(float (*funct)(vector<float> &), int bound_min, int bound_max); /// Initialize genetic algorithm to run for a certain function
    void run(); /// Run genetic algorithm. Status reset before every run.
    
private:
    int solution_number = 200; /// Number of population
    int dimension = 30;/// Dimension
    float bound_lower;///Lower bound of the function
    float bound_upper;///Higher bound of the function
    int tmax = 300; /// Maximum number of generation
    float crossover_rate = 0.8; /// Crossover rate
    float mutation_rate = 0.005; /// Mutation rate
    float mutation_range = 0.1; /// Mutation value range
    float mutation_percision = 1; /// Mutation precision
    float elitism_rate = 0.2; ///Elitism rate
    int elitism; /// Elitism

    Population population; /// Population
    Population population_new; /// Temporary population
    
    float (*f)(vector<float> &); /// Function
    
    vector<float> p1; /// Parent 1
    vector<float> p2; /// Parent 2
    vector<float> o1; /// Offspring 1
    vector<float> o2; /// Offspring 2
    
    int selectParent(); /// Select p1 and p2 parent;
    void selection(); /// Create parent1 and parent2 for mutation
    void crossover(); /// Crossover offspring1 with offspring2, happening according to random possibility
    void mutate(vector<float> &s); /// Mutate offspring
    void reduce(); /// Combine old population and new population. Size kept constant by eliminating low fitness value.
    void get_best_solution(); /// Get a better fx
};

#endif /* genetic_algorithm_h */
