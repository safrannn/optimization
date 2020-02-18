#include <vector>
#include <cmath>
#include "data_stats.h"
#include <iostream>

using namespace std;

DataStats::DataStats(){
    mean = 0;
    median = 0;
    stand = 0;
    range_low = 0;
    range_high = 0;
    time_avg = 0;
}
/// Generate analytical data
void DataStats::run()
{
    get_mean();
    get_median();
    get_stand();
    get_range();
    get_timeavg();
}

/// Get data data mean
void DataStats::get_mean()
{
    double sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    mean = (float)(sum / data.size());
}

/// Get data data median
void DataStats::get_median()
{
    vector<float> data_temp = data;
    sort(data_temp.begin(), data_temp.end());
    median = (data_temp[data_temp.size() / 2 - 1] + data_temp[data_temp.size() / 2]) / 2;
}

/// Get data data standard deviation
void DataStats::get_stand()
{
    double variance = 0.0;
    for (float v : data)
    {   variance += (v - mean) * (v - mean);
    }
    variance /= data.size();
    stand = (float)(sqrt(variance));
}

/// Get data data range
void DataStats::get_range(){
    float min = data[0];
    float max = data[0];
    for (int i = 1; i < data.size(); i++){
        if (data[i] < min){
            min = data[i];
        }else if (data[i] > max){
            max = data[i];
        }
    }
    range_low = min;
    range_high = max;
}

/// Get average time
void DataStats::get_timeavg(){
    double time_temp = 0.0;
    for (float v : time){
        time_temp += v;
    }
    time_avg = (float)(time_temp / data.size());
}
