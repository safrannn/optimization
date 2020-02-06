/// \file
/// @file func.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Math functions
/// @version 0.1
/// @date 2020-02-01

#ifndef func_h
#define func_h

#include <stdio.h>
#include <vector>

using namespace std;

/// 18 functions
namespace func {
    float schwefel(vector<float> &x);
    float firstDeJong(vector<float> &x);
    float rosenbrock(vector<float> &x);
    float rastrigin(vector<float> &x);
    float griewangk(vector<float> &x);
    float sineEnvelopeSineWave(vector<float> &x);
    float stretchedVSineWave(vector<float> &x);
    float ackleysOne(vector<float> &x);
    float ackleysTwo(vector<float> &x);
    float eggHolde(vector<float> &x);
    float rana(vector<float> &x);
    float pathological(vector<float> &x);
    float michalewicz(vector<float> &x);
    float mastersCosineWave(vector<float> &x);
    float quartic(vector<float> &x);
    float levy(vector<float> &x);
    float step(vector<float> &x);
    float alpine(vector<float> &x);
}

#endif

// =========================
// End of result.h
// =========================
