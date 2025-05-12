#ifndef SONAR_HPP
#define SONAR_HPP

#include <HCSR04.h>
#include <vector>

using namespace std;

class Sonar {
  
public:

  Sonar(uint8_t triggerPin, uint8_t* echoPins, uint8_t echoCount): triggerPin_(triggerPin), echoPins_(echoPins), echoCount_(echoCount) 
  {
    times_ = new long[echoCount];
    distances_ = new double[echoCount];
  }

  void begin() {
    HCSR04.begin(triggerPin_, echoPins_, echoCount_);
  }
  
  vector<double> measureDistanceCm() {
    HCSR04.measureDistanceCm(distances_);
    vector<double> vec(distances_, distances_ + echoCount_);
    
    return vec;
  }
  
private:
  double* distances_;
  uint8_t triggerPin_;
  uint8_t* echoPins_;
  uint8_t echoCount_;
  long* times_;

};

// // SET THESE VALUES TO MATCH YOUR WIRING -----------
// byte triggerPin = 21; //All triggers need to be connected to the same Arduino pin
// byte echoCount = 2; // This is the number of sensors that you're using with each echo pin connected to its own Arduino pin
// byte* echoPins = new byte[echoCount] { 18, 19 }; //These are the pin numbers of all echo pins
// // -------------------------------------------------

// long* times = new long[echoCount];
// double* distances = new double[echoCount];

// void setup () {
//   Serial.begin(9600);
//   HCSR04.begin(triggerPin, echoPins, echoCount);
// }

// void loop () {
  

//   HCSR04.measureDistanceCm(distances);
  
//   for (int i = 0; i < echoCount; i++) {
//     if (i > 0) Serial.print(" | ");
//     Serial.print(i + 1);
//     Serial.print(": ");
//     Serial.print(distances[i]);
//     Serial.print(" cm");
//   }
  
//   Serial.println("-----------------------------------");
//   delay(500);

// }

#endif // SONAR_HPP