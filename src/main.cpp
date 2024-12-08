#include <Arduino.h>
#include "HC_SR04Sensor.h"

HC_SRO4_Sensor *distanceSensor;

const int trigPin = 9;  // Trigger pin for the HC-SR04
const int echoPin = 10; // Echo pin for the HC-SR04

const int windowSize = 5; // reduce this would make it responsive but increases the noise.
const int distanceThreshold = 5; // proximty threshold

void setup()
{

  Serial.begin(9600);
  distanceSensor->begin(trigPin, echoPin, true, windowSize); 

}

void loop()
{

  bool inProximity = distanceSensor-> proximity_check(distanceThreshold); //turns the distance data to proximity with the set limit.

  long distance = distanceSensor-> measure_distance(); //measures the distance.

  // Print the distance for debugging
  if(inProximity)
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
  }
}