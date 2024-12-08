   #include "Filter.h"

   SMA::SMA (int window_size = 5) // increasing windowsize make reading smooth but less responsive
    {
      numReadings = window_size; 
      readings = new long[window_size];
      // Initialize all readings to 0
      for (int i = 0; i < numReadings; i++) {
        readings[i] = 0;
      }
    }
    SMA::~SMA() {
        delete[] readings; // Free dynamically allocated memory
    }
    long SMA::update(long new_reading) {
      // Subtract the last reading from the total to remove it
      total -= readings[currentIndex];

      // Add the new reading to the array and total
      readings[currentIndex] = new_reading;
      total += readings[currentIndex];

      // Move the index to the next position in the array
      currentIndex = (currentIndex + 1) % numReadings;

      // Calculate the average of the readings
      average = total / numReadings;

      return average;
    }