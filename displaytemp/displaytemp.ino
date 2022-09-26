#include "max6675.h"
#include <LiquidCrystal.h>
int thermoDO = 6;
int thermoCS = 7;
int thermoCLK = 8;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  lcd.print('Hello');
  delay(500);
}


void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  Serial.println(thermocouple.readCelsius());
  lcd.print(thermocouple.readCelsius());
  delay(1000);

}
