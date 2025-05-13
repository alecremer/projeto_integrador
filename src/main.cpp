#include "sonar.hpp"
#include <vector>
#include "pinout.hpp"
#include <memory>

using namespace std;

uint8_t* echoPins = new uint8_t[ECHO_COUNT] { ECHO_PIN_1, ECHO_PIN_2 }; //These are the pin numbers of all echo pins
Sonar sonar(TRIGGER_PIN, echoPins, ECHO_COUNT);

vector<double> distances{-1.00, -1.00};
shared_ptr<vector<double>> distances_ptr;



void beep(int t, int pin){
  digitalWrite(pin, HIGH);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  // delay(100);
  digitalWrite(pin, LOW);
  vTaskDelay(t / portTICK_PERIOD_MS);
  // delay(t);
}

int beep_calc(double distance){
  int t = map(distance, 0, 200, 1, 1000);
  return t;
}


void task_beep_1(void *parameter){
  for(;;){
    vector<double>::iterator it = distances_ptr->begin();
    if(*it != -1.00){
      int t = beep_calc(*it);
      beep(t, BUZZER_PIN_1);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}

void task_beep_2(void *parameter){
//   vector<double>::iterator it = distances_ptr->begin();
//   it++;
//   int t = beep_calc(*it);
//   beep(t, BUZZER_PIN_2);
}



void setup () {
  distances_ptr = make_shared<vector<double>>(distances);
  Serial.begin(9600);
  sonar.begin();
  pinMode(BUZZER_PIN_1, OUTPUT);
  xTaskCreate(
    task_beep_1,
    "task_beep_1",
    1000,
    NULL,
    1,
    NULL
  );
  // xTaskCreate(
  //   task_beep_2,
  //   "task_beep_2",
  //   1000,
  //   NULL,
  //   1,
  //   NULL
  // );
}

void loop () {
  
  distances = sonar.measureDistanceCm();
  *distances_ptr = distances;
  vector<double>::iterator it;
  
  vector<int> beep_pin = {BUZZER_PIN_1, BUZZER_PIN_2};
  vector<int>::iterator it_beep;

  for (it = distances.begin(); it != distances.end(); ++it) {
    if (it > distances.begin()) Serial.print(" | ");
    Serial.print(it - distances.begin() + 1);
    Serial.print(": ");
    Serial.print(*it);
    Serial.print(" cm");

    
  }
  
  Serial.println("-----------------------------------");
  delay(100);

}