#include "result.h"
#include "func.h"
#include "util.h"

#include <vector>
#include <cmath>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// Generate solution for function in dimension of DIMENSION
/// @param min minimum value for the function
/// @param max maximum value for the function
vector<Runner> runOne(float (*functn)(vector<float> &), int min, int max)
{
    vector<Runner> result;
    for (int d = 10; d <= 30; d += 10){
        Runner runner(d, functn, min, max);
        runner.run();
        result.push_back(runner);
    }
    return result;
}

void printAll(vector<vector<Runner>> results){
    printfx("func_fx", results);
    printResult("func_result", results);
}

/// Run all the 18 functions from func.h
void runAll()
{
    setSeed();
    
    vector<vector<Runner>> results;
    
    vector<Runner> schwefelResult = runOne(func::schwefel, -512, 512);
    results.push_back(schwefelResult);

    vector<Runner> firstDeJongResult = runOne(func::firstDeJong, -100, 100);
    results.push_back(firstDeJongResult);

    vector<Runner> rosenbrockResult = runOne(func::rosenbrock, -100, 100);
    results.push_back(rosenbrockResult);

    vector<Runner> rastriginResult = runOne(func::rastrigin, -30, 30);
    results.push_back(rosenbrockResult);

    vector<Runner> griewangkResult = runOne(func::griewangk, -500, 500);
    results.push_back(rosenbrockResult);

    vector<Runner> sineEnvelopeSineWaveResult = runOne(func::sineEnvelopeSineWave, -30, 30);
    results.push_back(sineEnvelopeSineWaveResult);

    vector<Runner> stretchedVSineWaveResult = runOne(func::stretchedVSineWave, -30, 30);
    results.push_back(stretchedVSineWaveResult);

    vector<Runner> ackleysOneResult = runOne(func::ackleysOne, -32, 32);
    results.push_back(ackleysOneResult);

    vector<Runner> ackleysTwoResult = runOne(func::ackleysTwo, -32, 32);
    results.push_back(ackleysTwoResult);

    vector<Runner> eggHoldeResult = runOne(func::eggHolde, -500, 500);
    results.push_back(eggHoldeResult);

    vector<Runner> ranaResult = runOne(func::rana, -500, 500);
    results.push_back(ranaResult);

    vector<Runner> pathologicalResult = runOne(func::pathological, -100, 100);
    results.push_back(pathologicalResult);

    vector<Runner> michalewiczResult = runOne(func::michalewicz, 0, M_PI);
    results.push_back(michalewiczResult);

    vector<Runner> mastersCosineWaveResult = runOne(func::mastersCosineWave, -30, 30);
    results.push_back(mastersCosineWaveResult);

    vector<Runner> quarticResult = runOne(func::quartic, -100, 100);
    results.push_back(quarticResult);

    vector<Runner> levyResult = runOne(func::levy, -10, 10);
    results.push_back(levyResult);

    vector<Runner> stepResult = runOne(func::step, -100, 100);
    results.push_back(stepResult);

    vector<Runner> alpineResult = runOne(func::alpine, -100, 100);
    results.push_back(alpineResult);
    
    printAll(results);
}

