  #include "max6675.h"
  
  int thermoDO1 = 4;
  int thermoCS1 = 5;
  int thermoCLK1 = 6;
int thermoDO2 = 7;
int thermoCS2 = 8;
int thermoCLK2 = 9;

MAX6675 thermocouple(thermoCLK1, thermoCS1, thermoDO1);

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
  Serial.print("C1 = "); 
  Serial.println(thermocouple.readCelsius());
  Serial.print("Temp = ");
  Serial.println(thermocouple.spiread());
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}
