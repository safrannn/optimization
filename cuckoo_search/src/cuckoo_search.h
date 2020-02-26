#ifndef moth_fire
#define moth_fire

#include "population.h"
#include "data_stats.h"

using namespace std;

class CS{
public:
    CS(int strat, float (*f)(vector<float> &), float l, float u);
    vector<float> run();

private:
    int strategy = 0;
    int gmax = 2500; /// Max generation
    float alpha0 = 0.01; /// Alpha value for generating trial vector for each generation
    float pa_max = 0.25;
    int psize = 200; /// Size of population
    int dimension = 30; /// Solution dimension
    Population population; /// Cuckoo bird population

    float (*function)(vector<float> &); /// Cost function
    float bound_low; /// Solution low bound
    float bound_high; /// Solution high bound

    float lambda = 1.5; /// Lambda for levy flight
    vector<float> levy_flight_data; /// Levy flight data used for random walk for each generation
    void levy_flight_generator(); /// Generate levy flight data

    void reset(); /// reset a run
};
#endif //moth_fire
