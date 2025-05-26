#include <vector>
#include <memory>

#include "pinout.hpp"
#include "sonar.hpp"
#include "buzzer.hpp"

using namespace std;

uint8_t* echoPins = new uint8_t[ECHO_COUNT] { ECHO_PIN_1, ECHO_PIN_2 }; //These are the pin numbers of all echo pins
Sonar sonar(TRIGGER_PIN, echoPins, ECHO_COUNT);
vector<double> distances_buffer;
double distance1{-1.00};
double distance2{-1.00};
shared_ptr<double> distance1_ptr = make_shared<double>(distance1);
shared_ptr<double> distance2_ptr = make_shared<double>(distance2);

Buzzer buzzer1(100, BUZZER_PIN_1, distance1_ptr);
Buzzer buzzer2(100, BUZZER_PIN_2, distance2_ptr);



// void beep(int t, int pin){
//   digitalWrite(pin, HIGH);
//   vTaskDelay(100 / portTICK_PERIOD_MS);
//   // delay(100);
//   digitalWrite(pin, LOW);
//   vTaskDelay(t / portTICK_PERIOD_MS);
//   // delay(t);
// }



void task_beep_1(void *parameter){
  buzzer1.beep_task(parameter);
}

void task_beep_2(void *parameter){
  buzzer2.beep_task(parameter);
}

// void task_beep_2(void *parameter){
//   for(;;){
//     vector<double>::iterator it = distances_ptr->begin();
//     if(*it != -1.00){
//       int t = beep_calc(*it);
//       beep(t, BUZZER_PIN_2);
//     }
//     vTaskDelay(100 / portTICK_PERIOD_MS);

//   }
// }



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
  xTaskCreate(
    task_beep_2,
    "task_beep_2",
    1000,
    NULL,
    1,
    NULL
  );
}

void loop () {
  
  distances_buffer = sonar.measureDistanceCm();
  vector<double>::iterator it = distances_buffer.begin();

  distance1 = *it;
  distance2 = *(it + 1);
  *distance1_ptr = distance1;
  *distance2_ptr = distance2;
  
  
  for (vector<double>::iterator it = distances_buffer.begin(); it != distances_buffer.end(); ++it) {
    if (it > distances_buffer.begin()) Serial.print(" | ");
    Serial.print(it - distances_buffer.begin() + 1);
    Serial.print(": ");
    Serial.print(*it);
    Serial.print(" cm");

    
  }
  
  Serial.println("-----------------------------------");
  delay(100);

}