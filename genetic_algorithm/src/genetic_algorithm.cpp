#include <vector>
#include <array>
#include <cmath>
#include <iostream>

#include "genetic_algorithm.h"
#include "population.h"
#include "../lib/mt64.h"

using namespace std;


/// Initialize genetic algorithm to run for a certain function
/// @param f function
/// @param l low bound for x
/// @param u high bound for x
Genetic_algorithm::Genetic_algorithm(float (*funct)(vector<float> &), float l, float u){
    f = funct;
    bound_low = l;
    bound_up = u;

    elitism = (int)(elitism_rate * population_size);
}
    

/// Select an index from the population as parent
int Genetic_algorithm::selectParent(){
    float r = (float)genrand64_real1() * population.fitness_total;
    float s = 0;
    while (s < population_size - 1 && r > 0){
        r -= population.fitness[s];
        s += 1;
    }
    return s;
}


/// Create parent1 and parent2 for mutation
void Genetic_algorithm::selection(){
    p1 = population.population[selectParent()];
    p2 = population.population[selectParent()];
}


/// Crossover offspring1 with offspring2, happening according to random possibility
void Genetic_algorithm::crossover(){
    o1.clear();
    o1.reserve(dimension);
    o2.clear();
    o2.reserve(dimension);
    if (genrand64_real1() < crossover_rate){
        int d = (int)(1 + genrand64_real3() * (dimension - 1));
        o1.insert(o1.end(),p1.begin(),p1.begin()+d);
        o1.insert(o1.end(),p2.begin()+d,p2.end());
        o2.insert(o2.end(),p2.begin(),p2.begin()+d);
        o2.insert(o2.end(),p1.begin()+d,p1.end());
    }else{
        o1 = p1;
        o2 = p2;
    }
}


/// Mutate offspring
/// @param s offspring
void Genetic_algorithm::mutate(vector<float> &s){
    for (int i = 0; i < dimension; i++){
        if ((float)genrand64_real1() < mutation_rate){
            float rand = -2 + (float)genrand64_real1()*2;
            float number = rand * (bound_up - bound_low) * mutation_range * pow(2, (-1 * (float)genrand64_real1() * mutation_percision));
            s[i] += number;
            
            if (s[i] < bound_low){
                s[i] = bound_low;
            }else if (s[i] > bound_up){
                s[i] = bound_up;
            }
        }
    }
}


/// Combine old population and new population. Size kept constant by eliminating high cost value.
void Genetic_algorithm::reduce(){
    population.sort_by_cost();
    population_new.sort_by_cost();
    for (int s = elitism; s < population_size; s++){
        population.population[s] = population_new.population[s-elitism];
    }
}


/// Get a better fx
void Genetic_algorithm::get_best_solution(){
    float current_best = population.cost[0];
    if (current_best < f_best){
        f_best = current_best;
        solution_best = population.population[0];
    }
    f_best_history.push_back(f_best);
}


/// Run genetic algorithm. Status reset before every run.
void Genetic_algorithm::run(){
    // reset run
    f_best = INT_MAX;
    f_best_history.clear();
    
    // init population
    population.init(population_size, dimension, f, bound_low, bound_up);
    population.generation();
    population.evaluate();
    
    // init new population
    population_new.init(population_size, dimension, f, bound_low, bound_up);
    
    for (int t = 0; t < tmax; t++){
        population_new.reset();

        for (int s = 0; s < population_size; s+=2){
            // selection
            selection();

            // crossover
            crossover();

            // mutation
            mutate(o1);
            mutate(o2);
            population_new.population.push_back(o1);
            population_new.population.push_back(o2);
        }
        // evaluate new population
        population_new.evaluate();

        // combine population and population_new into population
        reduce();

        population.evaluate();
        
        get_best_solution();
    }
}

