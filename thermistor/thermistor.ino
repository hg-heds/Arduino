#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
int thermistor_black = A0;
int thermistor_white = A1;
int thermistor_hg = A2;
float white_res = 10.02;
float black_res = 9.9;
float hg_res = 9.88;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

}

void loop() {
 float tcouple = thermocouple.readCelsius();
 float tb = analogRead(thermistor_black);
 float bk = black_res * (1024.0/tb-1.0);
 float tw = analogRead(thermistor_white);
 float wt = white_res * (1024.0/tb-1.0);
 float th = analogRead(thermistor_hg);
 float hg = hg_res * (1024.0/th-1.0);
 Serial.print(analogRead(thermistor_black));
 Serial.print(" ");
 Serial.print(analogRead(thermistor_white));
 Serial.print(" ");
 Serial.print(analogRead(thermistor_hg)); 
 Serial.print("    --    ");
 Serial.print("T: ");
 Serial.print(tcouple);
 Serial.print(" R_w: ");
 Serial.print(wt);
 Serial.print(" R_b: ");
 Serial.print(bk);
 Serial.print(" R_h: ");
 Serial.println(hg);
 delay(1000);

}
