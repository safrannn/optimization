#include <iostream>
#include <cmath>
#include <vector>

#include "run.h"
#include "func.h"
#include "data_stats.h"

using namespace std;

int main() {
    setSeed();
    int experiment = 50;
    vector<DataStats> result_best;
 
    result_best.push_back(runFunc(experiment, "schwefel", func::schwefel, -512, 512)); //
    result_best.push_back(runFunc(experiment, "firstDeJong", func::firstDeJong, -100, 100));
    result_best.push_back(runFunc(experiment, "rosenbrock", func::rosenbrock, -100, 100)); /// ?????
    result_best.push_back(runFunc(experiment, "rastrigin", func::rastrigin, -30, 30));
    result_best.push_back(runFunc(experiment, "griewangk", func::griewangk, -500, 500));
    result_best.push_back(runFunc(experiment, "sineEnvelopeSineWave", func::sineEnvelopeSineWave, -30, 30));
    result_best.push_back(runFunc(experiment, "stretchedVSineWave", func::stretchedVSineWave, -30, 30));
    result_best.push_back(runFunc(experiment, "ackleysOne", func::ackleysOne, -32, 32));
    result_best.push_back(runFunc(experiment, "ackleysTwo", func::ackleysTwo, -32, 32));
    result_best.push_back(runFunc(experiment, "eggHolder", func::eggHolder, -500, 500));//?
    result_best.push_back(runFunc(experiment, "rana", func::rana, -500, 500));//?
    result_best.push_back(runFunc(experiment, "pathological", func::pathological, -100, 100));
    result_best.push_back(runFunc(experiment, "michalewicz", func::michalewicz, 0, M_PI));
    result_best.push_back(runFunc(experiment, "mastersCosineWave", func::mastersCosineWave, -30, 30));
    result_best.push_back(runFunc(experiment, "quartic", func::quartic, -100, 100));
    result_best.push_back(runFunc(experiment, "levy", func::levy, -10, 10));
    result_best.push_back(runFunc(experiment, "step", func::step, -100, 100));
    result_best.push_back(runFunc(experiment, "alpine", func::alpine, -100, 100));

    output_all(result_best);
    std::cout << "Code Finish!\n";
    return 0;
}
