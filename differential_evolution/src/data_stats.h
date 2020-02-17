/// @file data_stats.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief data analysis
/// @version 1.0
/// @date 2020-02-11

#ifndef data_stats_h
#define data_stats_h

#include <vector>

using namespace std;

class DataStats
{
public:
    float mean = INT_MAX;
    float median = INT_MAX;
    float stand;
    float range[2];
    float time_avg;
    vector<float> time;
    vector<float> data;

    void run();

private:
    void get_mean();
    void get_median();
    void get_stand();
    void get_range();
};

#endif //data_stats_h
