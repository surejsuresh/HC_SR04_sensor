
#ifndef HC_SR04_SENSOR_H
#define HC_SR04_SENSOR_H

#include <Arduino.h>

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

// sensor
class HC_SRO4_Sensor
{
private:
    static SMA *filter;
    static HC_SRO4_Sensor *instance;
    // pins
    const int trigPin;
    const int echoPin;

    HC_SRO4_Sensor() = delete;
    HC_SRO4_Sensor(int trigger_pin, int echo_pin);

    HC_SRO4_Sensor(const HC_SRO4_Sensor &) = delete;
    HC_SRO4_Sensor &operator=(const HC_SRO4_Sensor &) = delete;

public:
    HC_SRO4_Sensor *begin(int trigger_pin, int echo_pin, bool sma_filter = true, int window_size = 5);
    long measure_distance();
    bool proximity_check(long distanceThreshold);
};
#endif