#ifndef particle_swamp
#define particle_swamp

#include "population.h"
#include "data_stats.h"

using namespace std;

class PS{
public:
    PS(float (*f)(vector<float> &), float l, float u);
    vector<float> run();


private:
    int tmax = 100;
    float c1 = 0.5;
    float c2 = 0.5;

    int pop_size = 200; /// Size of population
    int pop_dimension = 30; /// Dimension
    Population population;

    float (*function)(vector<float> &);
    float bound_low; ///Lower bound of the function
    float bound_up; ///Higher bound of the function

};
#endif //particle_swamp
