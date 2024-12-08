

#include "HC_SR04Sensor.h"

HC_SRO4_Sensor::HC_SRO4_Sensor(int trigger_pin, int echo_pin) : trigPin(trigger_pin), echoPin(echo_pin) {}

HC_SRO4_Sensor *HC_SRO4_Sensor::begin(int trigger_pin, int echo_pin, bool sma_filter = true, int window_size = 5)
{
    if (instance == nullptr)
    {
        instance = new HC_SRO4_Sensor(trigger_pin, echo_pin);
        if (sma_filter)
            filter = new SMA(window_size);
        else
            filter = nullptr;
        const_cast<int &>(trigPin) = trigger_pin;
        const_cast<int &>(echoPin) = echo_pin;

        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }
    return instance;
}

long HC_SRO4_Sensor::measure_distance()
{
    // Send a pulse to trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the time it takes for the pulse to return
    long duration = pulseIn(echoPin, HIGH);

    // Calculate the distance in centimeters
    long dist = duration * 0.0344 / 2; // Speed of sound = 343m/s, so distance = (duration * 0.0344) / 2

    // Apply filter
    long distance;
    
    if (filter != nullptr)
        distance = filter->update(dist);
    else
        distance = dist;
    return distance;
}
bool HC_SRO4_Sensor::proximity_check(long distanceThreshold)
{
    long distance = measure_distance();
    if (distance <= distanceThreshold)
        return true;
    return false;
}
HC_SRO4_Sensor *HC_SRO4_Sensor::instance = nullptr;
SMA *HC_SRO4_Sensor::filter = nullptr;