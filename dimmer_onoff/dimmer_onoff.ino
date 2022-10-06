#include "RBDdimmer.h"
#include "max6675.h"

int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;

dimmerLamp dimmer(12);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float setPoint = 0;
float range = 5;
float temp = 0;
int power = 100;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
  delay(1000);
}

void loop() {
  setPoint = map(analogRead(0), 0, 1023, 30, 100);
  temp = thermocouple.readCelsius();
  Serial.print(setPoint); 
  Serial.print(" -- ");
  Serial.print(temp);
  Serial.print(" -- ");
  if (temp < setPoint - range){
    power = 0;
  }
  if (temp > setPoint + range){
    power = 100;
  }
  dimmer.setPower(power);
  Serial.println(power);
  delay(250);
}
