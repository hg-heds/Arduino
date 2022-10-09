#include "RBDdimmer.h"
#include "max6675.h"

int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;

dimmerLamp dimmer(12);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float setPoint = 0;
float range = 3;
float temp = 0;
int power = 100;

void setup() {
  Serial.begin(9600);
  dimmer.begin(TOGGLE_MODE, OFF);
  dimmer.toggleSettings(0, 100);
  dimmer.setState(ON);
  delay(1000);
}

void loop() {
  temp = thermocouple.readCelsius();
  Serial.print(power); 
  Serial.print(" -- ");
  Serial.println(temp);
  delay(1000);
}
