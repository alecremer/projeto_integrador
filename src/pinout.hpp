#ifndef PINOUT_HPP
#define PINOUT_HPP

#include <cstdint>

using namespace std;

// ----------------------------
// SONAR
// ----------------------------
#define ECHO_COUNT 2
#define TRIGGER_PIN 21
#define ECHO_PIN_1 18
#define ECHO_PIN_2 19

// // SET THESE VALUES TO MATCH YOUR WIRING -----------
// uint8_t triggerPin = TRIGGER_PIN; //All triggers need to be connected to the same Arduino pin
// // uint8_t echoCount = 2; // This is the number of sensors that you're using with each echo pin connected to its own Arduino pin
// uint8_t* echoPins = new uint8_t[ECHO_COUNT] { ECHO_PIN_1, ECHO_PIN_2 }; //These are the pin numbers of all echo pins
// // -------------------------------------------------


// ----------------------------
// BUZZER
// ----------------------------
#define BUZZER_PIN_1 22
#define BUZZER_PIN_2 23

#endif // PINOUT_HPP