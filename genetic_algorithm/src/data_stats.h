/// @file data_stats.h
/// @author Cheng Su (csu@cwu.edu)
/// @brief data analysis
/// @version 0.1
/// @date 2020-02-05


#ifndef data_stats_h
#define data_stats_h

#include <vector>

using namespace std;

class DataStats
{
public:
    float mean = INT_MAX;
    float median = INT_MAX;
    float stand = INT_MAX;
    float range_low;
    float range_high;
    float time_avg = 0;
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
