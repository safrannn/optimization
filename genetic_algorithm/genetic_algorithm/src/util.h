/// @file util.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief Analyze result 
/// @version 0.1
/// @date 2020-02-05

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <vector>

using namespace std;

/// Generate analytical results
class DataStats
{
public:
    float mean;
    float median;
    float stand;
    float range[2];
    vector<float> data;
    
    void run();
    
private:
    void get_mean();
    void get_median();
    void get_stand();
    void get_range();
};

#endif /* util_hpp */
