#include "util.h"
#include <cmath>

/// Generate analytical datas
void DataStats::run()
{
    get_mean();
    get_median();
    get_stand();
    get_range();
}

/// Get data data mean
void DataStats::get_mean()
{
    float sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    mean = sum / data.size();
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
    float variance = 0.0;
    for (int i = 0; i < data.size(); i++)
    {   variance += pow(data[i] - mean, 2);
    }
    variance /= data.size();
    stand = sqrt(variance);
}

/// Get data data range
void DataStats::get_range(){
    float min = data[0];
    float max = data[1];
    for (int i = 0; i < data.size(); i++){
        if (data[i] < min){
            min = data[i];
        }else{
            max = data[i];
        }
    }
    range[0] = min;
    range[1] = max;
}

