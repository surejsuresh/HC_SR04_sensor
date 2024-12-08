#ifndef FILTER_H
#define FILTER_H

class SMA //simple moving average filter
{
private:
    int numReadings;    // Number of readings to average (window size)
    long* readings = nullptr;   // Array to store the last 'numReadings' distance values
    int currentIndex =0;         // Current index in the readings array
    long total =0.0;               // Total of the last 'numReadings' readings
    long average =0;             // Calculated average value
    
public:
    SMA (int window_size = 5); // increasing windowsize make reading smooth but less responsive
    ~SMA();
    long update(long new_reading);
};

#endif
