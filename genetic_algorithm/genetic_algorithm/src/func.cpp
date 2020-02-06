#include "func.h"
#include <cmath>
#include <vector>

using namespace std;

/// Function 1, Implementation of Schwefel’s function
/// @param x descriptionx Vector of float
float func::schwefel(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        result += (-1.0 * x[i]) * sin(sqrt(fabs(x[i])));
    }
    return 418.9829 * x.size() - result;
}

/// Function 2, Implementation of 1st De Jong's function
/// @param x descriptionx Vector of float
float func::firstDeJong(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        result += x[i]*x[i];
    }
    return result;
}

/// Function 3, Implementation of Rosenbrock's function
/// @param x descriptionx Vector of float
float func::rosenbrock(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = x[i] * x[i] - x[i+1];
        float b = 1 - x[i];
        result += 100 * a * a + b * b;
    }
    return result;
}

/// Function 4, Implementation of Rastrigin's function
/// @param x descriptionx Vector of float
float func::rastrigin(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        result += x[i] * x[i] - 10.0 * cos((2 * M_PI * x[i]));
    }
    return 10 * x.size() * result;
}

/// Function 5, Implementation of Griewangk function
/// @param x descriptionx Vector of float
float func::griewangk(vector<float> &x){
    float sum = 0;
    float product = 1;
    for (int i = 0; i < x.size() ; i++){
        sum += x[i] * x[i] / 4000;
        product *= cos(x[i]/sqrt(i+1));
    }
    return 1.0 + sum - product;
}

/// Function 6, Implementation of Sine Envelope Sine Wave function
/// @param x descriptionx Vector of float
float func::sineEnvelopeSineWave(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float sqr = x[i] * x[i] + x[i+1] * x[i+1];
        float a = sqr - 0.5;
        float b = 1 + 0.001*(sqr);
        result += 0.5 + sin(a * a) / (b * b);
    }
    return -1.0 * result;
}

/// Function 7, Implementation of Stretched V Sine Wave function
/// @param x descriptionx Vector of float
float func::stretchedVSineWave(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = pow(x[i]*x[i]+x[i+1]*x[i+1],1/4);
        float b = pow(50 * pow(x[i]*x[i]+x[i+1]*x[i+1],1/10),2);
        result += a*sin(b) + 1;
    }
    return result;
}

/// Function 8, Implementation of Ackley's One function
/// @param x descriptionx Vector of float
float func::ackleysOne(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = sqrt(x[i]*x[i]+x[i+1]*x[i+1]) / pow(M_E,0.2);
        float b = 3.0 * (cos(2.0 * x[i]) + sin(2.0 * x[i+1]));
        result += a + b;
    }
    return result;
}

/// Function 9, Implementation of Ackley's Two function
/// @param x descriptionx Vector of float
float func::ackleysTwo(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = 0.2 * sqrt((x[i]*x[i]+x[i+1]*x[i+1])/2);
        float b = 0.5 * (cos(2 * M_PI* x[i]) + sin(2 * M_PI* x[i+1]));
        result += 20 + M_E - 20 / pow(M_E, a)-pow(M_E, b);
    }
    return result;
}

/// Function 10, Implementation of Egg Holder  function
/// @param x descriptionx Vector of float
float func::eggHolder(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = -1 * x[i] * sin(sqrt(fabs(x[i] - x[i+1] - 47)));
        float b = -1 * (x[i+1]+47) * sin(sqrt(fabs(x[i]/2 + x[i+1] + 47)));
        result += a + b;
    }
    return result;
}

/// Function 11, Implementation of Rana function
/// @param x descriptionx Vector of float
float func::rana(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size() - 1; i++){
        float a = sqrt(fabs(x[i+1]-x[i]+1));
        float b = sqrt(fabs(x[i+1]+x[i]+1));
        result += x[i] * sin(a) * cos(b) + (x[i+1]+1) * cos(a) * sin(b);
    }
    return result;
}

/// Function 12, Implementation of Pathological function
/// @param x descriptionx Vector of float
float func::pathological(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size()- 1; i++){
        float a = sin(fabs(100 * x[i] * x[i] + x[i+1] * x[i+1]));
        float b = x[i] * x[i] - 2 * x[i] * x[i+1] + x[i+1] * x[i+1];
        result += 0.5 + (a - 0.5)/(1 + 0.001 * b * b);
    }
    return result;
}

/// Function 13, Implementation of Michalewicz function
/// @param x descriptionx Vector of float
float func::michalewicz(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        float a = sin((i+1) * x[i] * x[i]/M_PI);
        result += sin(x[i]) * pow(a,20);
    }
    return -result;
}

/// Function 14, Implementation of Masters Cosine Wave function
/// @param x descriptionx Vector of float
float func::mastersCosineWave(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        float a = x[i] * x[i] + x[i+1] * x[i+1] + 0.5 * x[i] * x[i+1];
        result += pow(M_E,- a / 8.0) * cos(4 * sqrt(a));
    }
    return -result;
}

/// Function 15, Implementation of Quartic function
/// @param x descriptionx Vector of float
float func::quartic(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        result += (i + 1) * pow(x[i], 4);
    }
    return result;
}

/// Function 16, Implementation of Levy function
/// @param x descriptionx Vector of float
float func::levy(vector<float> &x){
    float result = sin(M_PI * (1 + (x[0]-1)/4));
    result = result * result;
    float wn = 1 + (x[x.size()-1] - 1) / 4;
    float wna = pow(wn - 1, 2) * (1 + pow(2 * M_PI * wn, 2));
    for (int i = 0; i < x.size() - 1; i++){
        float w = 1 + (x[i] - 1) / 4;
        result += pow(w-1,2) * (1 + 10 * pow(sin(M_PI * w + 1), 2)) + wna;

    }
    return result;
}

/// Function 147 Implementation of Step function
/// @param x descriptionx Vector of float
float func::step(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        result += (fabs(x[i]) + 0.5) * (fabs(x[i]) + 0.5);
    }
    return result;
}

/// Function 18, Implementation of Alpine function
/// @param x descriptionx Vector of float
float func::alpine(vector<float> &x){
    float result = 0;
    for (int i = 0; i < x.size(); i++){
        result += fabs(x[i] * sin(x[i]) + 0.1 * x[i]);
    }
    return result;
}

