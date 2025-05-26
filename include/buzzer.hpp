#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <vector>
#include <Arduino.h>
#include <memory>

using namespace std;

class Buzzer{
public:

    Buzzer(const int& delay, const int& pin, shared_ptr<double> distance): delay_high(delay), pin(pin), distance_ptr(distance){}

    void beep(int t){
        digitalWrite(pin, HIGH);
        vTaskDelay(delay_high / portTICK_PERIOD_MS);
        digitalWrite(pin, LOW);
        vTaskDelay(t / portTICK_PERIOD_MS);
    }

    int beep_calc(double distance){
        int t = map(distance, 0, 200, 1, 1000);
        return t;
    }

    void beep_task(void *parameter){
        for(;;){
            double d = *distance_ptr;
            if(d > 0){
                int t = beep_calc(*distance_ptr);
                beep(t);
                
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
    
private:
    int delay_high;
    int pin;
    shared_ptr<double> distance_ptr;

};

#endif // BUZZER_HPP