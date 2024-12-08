
#ifndef HC_SR04_SENSOR_H
#define HC_SR04_SENSOR_H

#include <Arduino.h>
#include <Filter.h>

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