#ifndef cuckoo_search_gaussian
#define cuckoo_search_gaussian


#include "population.h"
#include "data_stats.h"

using namespace std;

class CSG{
public:
    CSG(int strat, float (*f)(vector<float> &), float l, float u);
    vector<float> run();

private:
    int gmax = 2000; /// Max generation
    float alpha0 = 0.05; /// Alpha value for generating trial vector for each generation
    int strategy = 0;
    float pa = 0.25;
    float pa_max = 0.25;
    float miu = 0.0001;
    float sigma0 = 8;
    int psize = 200; /// Size of population
    int dimension = 30; /// Solution dimension
    Population population; /// Cuckoo bird population

    float (*function)(vector<float> &); /// Cost function
    float bound_low; /// Solution low bound
    float bound_high; /// Solution high bound

    void reset(); /// reset a run
};

#endif //cuckoo_search_gaussian
