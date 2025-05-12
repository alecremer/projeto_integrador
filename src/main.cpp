#include "sonar.hpp"
#include <vector>

using namespace std;

// SET THESE VALUES TO MATCH YOUR WIRING -----------
uint8_t triggerPin = 21; //All triggers need to be connected to the same Arduino pin
uint8_t echoCount = 2; // This is the number of sensors that you're using with each echo pin connected to its own Arduino pin
uint8_t* echoPins = new uint8_t[echoCount] { 18, 19 }; //These are the pin numbers of all echo pins
// -------------------------------------------------

Sonar sonar(triggerPin, echoPins, echoCount);

void setup () {
  Serial.begin(9600);
  sonar.begin();
}

void loop () {
  
  vector<double> distances = sonar.measureDistanceCm();
  vector<double>::iterator it;
  
  for (it = distances.begin(); it != distances.end(); ++it) {
    if (it > distances.begin()) Serial.print(" | ");
    Serial.print(it - distances.begin() + 1);
    Serial.print(": ");
    Serial.print(*it);
    Serial.print(" cm");
  }
  
  Serial.println("-----------------------------------");
  delay(500);

}