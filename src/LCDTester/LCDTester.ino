/*
  Chris Nethercott
  LCD Tester
*/

#include <Wire.h>
#include <LiquidCrystal_I2C> // Uses the library that is in the orgo.

LiquidCrystal_I2C lcd(0x27, 16, 2); // 16,2 LCD. Use a I2C finder to find the address.

void setup() {
  lcd.begin();
  lcd.backlight();
  
  lcd.print("Hello World!");
  lcd.setCursor(0,1);
  lcd.print("It Works!");
}

void loop() {}
