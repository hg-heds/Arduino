#include <RBDdimmer.h>
#include "max6675.h"

int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;

dimmerLamp dimmer(12);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

int outVal = 0;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
}

void loop() 
{
  outVal = map(analogRead(0), 465, 1023, 0, 100);
  Serial.print(outVal); 
  Serial.print(' -- ');
  Serial.println(thermocouple.readCelsius());
  dimmer.setPower(outVal);
  delay(500)
}
