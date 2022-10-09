#include "RBDdimmer.h"
#include "max6675.h"
#define window 4
int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;

dimmerLamp dimmer(12);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float setPoint = 0;
float temp[window];
int pos = 0;
float T = 0;
int power = 100;
float e = 0;

int setPower(float err){
    float p = 20*err;
    if (p > 100) p = 100;
    if (p < 0) p = 0;
    return (int)p;
}

void setup() {
    Serial.begin(9600);
    for(int i = 0; i<window;i++){
        temp[i] = thermocouple.readCelsius();
    }
    dimmer.begin(NORMAL_MODE, ON);
    delay(1000);
}

void loop() {
    setPoint = map(analogRead(0), 0, 1023, 30, 90);
    temp[pos] = thermocouple.readCelsius();
    if (pos++ == window) pos = 0;
    T = 0;
    for(int i = 0; i<window; i++){
        T += temp[i];
    }
    T /= window;
    e = setPoint - T;
    power = setPower(e);
    Serial.print(setPoint); 
    Serial.print(" -- ");
    Serial.print(T);
    Serial.print(" -- ");
    dimmer.setPower(100-power);
    Serial.println(power);
    delay(500);
}
