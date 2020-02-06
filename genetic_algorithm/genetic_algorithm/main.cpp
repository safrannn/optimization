#include <iostream>
#include <cmath>

#include "src/run.h"
#include "src/func.h"

int main(int argc, const char * argv[]) {
    setSeed();
    int experiment = 50;
    
    runFunc(experiment, "schwefel", func::schwefel, -512, 512);
    runFunc(experiment, "firstDeJong", func::firstDeJong, -100, 100);
    runFunc(experiment, "rosenbrock", func::rosenbrock, -100, 100);
    runFunc(experiment, "rastrigin", func::rastrigin, -30, 30);
    runFunc(experiment, "griewangk", func::griewangk, -500, 500);
    runFunc(experiment, "sineEnvelopeSineWave", func::sineEnvelopeSineWave, -30, 30);
    runFunc(experiment, "stretchedVSineWave", func::stretchedVSineWave, -30, 30);
    runFunc(experiment, "ackleysOne", func::ackleysOne, -32, 32);
    runFunc(experiment, "ackleysTwo", func::ackleysTwo, -32, 32);
    runFunc(experiment, "eggHolder", func::eggHolder, -500, 500);
    runFunc(experiment, "rana", func::rana, -500, 500);
    runFunc(experiment, "pathological", func::pathological, -100, 100);
    runFunc(experiment, "michalewicz", func::michalewicz, 0, M_PI);
    runFunc(experiment, "mastersCosineWave", func::mastersCosineWave, -30, 30);
    runFunc(experiment, "quartic", func::quartic, -100, 100);
    runFunc(experiment, "levy", func::levy, -10, 10);
    runFunc(experiment, "step", func::step, -100, 100);
    runFunc(experiment, "alpine", func::alpine, -100, 100);
    
    std::cout << "Code Finish!\n";
    return 0;
}
