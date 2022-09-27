#include <RBDdimmer.h>
#include "max6675.h"

int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;

int tdo = 11;
int tcs = 10;
int tclk = 9;

dimmerLamp dimmer(12);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
MAX6675 thermocouple_lab(tclk, tcs, tdo);

int outVal = 0;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
  delay(1000);
}

void loop() {
  outVal = map(analogRead(0), 0, 534, 0, 100);
  Serial.print(outVal); 
  Serial.print(" -- ");
  Serial.print(thermocouple.readCelsius());
  Serial.print(" -- ");
  Serial.println(thermocouple_lab.readCelsius());
  dimmer.setPower(outVal);
  delay(1000);
}
