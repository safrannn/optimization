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

/// Population
class Population{
public:
    void init(int s, int d, float (*f)(vector<float> &), float l, float u);

    vector<vector<float>> data;
    vector<vector<float>> velocity;
    vector<float> cost;

    vector<vector<float>> particle_best_data;
    vector<float> particle_best_cost;

    vector<float> global_best_data;
    float global_best_cost;

    void reset(); /// Reset the population for new run

private:
    int size;
    int dimension;
    int bound_low;
    int bound_up;
    float (*function)(vector<float> &);

    void generate();
};

#endif /* population_hpp */
