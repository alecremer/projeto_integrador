#include <vector>
#include <memory>

#include "pinout.hpp"
#include "sonar.hpp"
#include "buzzer.hpp"
#include "sonar_fusion.hpp"

using namespace std;

double range = 200.00;
double delta = 20.0;
SonarFusion sonar_fusion(delta, range);

uint8_t* echoPins = new uint8_t[ECHO_COUNT] { ECHO_PIN_1, ECHO_PIN_2 }; //These are the pin numbers of all echo pins
Sonar sonar(TRIGGER_PIN, echoPins, ECHO_COUNT);
vector<double> distances_buffer;
double distance1{-1.00};
double distance2{-1.00};
double distance_fusion{-1.00};
shared_ptr<double> distance1_ptr = make_shared<double>(distance1);
shared_ptr<double> distance2_ptr = make_shared<double>(distance2);
shared_ptr<double> distance_fusion_ptr = make_shared<double>(distance_fusion);

Buzzer buzzer1(100, BUZZER_PIN_1, distance_fusion_ptr);


void task_beep_1(void *parameter){
  buzzer1.beep_task(parameter);
}


void setup () {

  Serial.begin(9600);
  sonar.begin();
  
  pinMode(BUZZER_PIN_1, OUTPUT);
  pinMode(BUZZER_PIN_2, OUTPUT);

  xTaskCreate(
    task_beep_1,
    "task_beep_1",
    1000,
    NULL,
    1,
    NULL
  );
}

void update_distances(bool print = false){
  
  distances_buffer = sonar.measureDistanceCm();
  vector<double>::iterator it = distances_buffer.begin();

  distance1 = *it;
  distance2 = *(it + 1);
  *distance1_ptr = distance1;
  *distance2_ptr = distance2;

  distance_fusion = sonar_fusion.fusion_distances(distance1, distance2);
  *distance_fusion_ptr = distance_fusion;
  
  if(print){
      for (vector<double>::iterator it = distances_buffer.begin(); it != distances_buffer.end(); ++it) {
        if (it > distances_buffer.begin()) Serial.print(" | ");
        Serial.print(it - distances_buffer.begin() + 1);
        Serial.print(": ");
        Serial.print(*it);
        Serial.print(" cm");
      
    }
    Serial.print(" | Fusion: ");
    Serial.print(distance_fusion);
    Serial.print(" cm");
    Serial.println("-----------------------------------");
  }
}
void loop () {
  
  
  update_distances(true);
  
  delay(100);

}