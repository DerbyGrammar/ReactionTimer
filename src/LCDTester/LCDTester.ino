#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Hello World");
  Serial.print("Write some stuff here, to display it on the LCD!");
}

void loop() {
  if(Serial.available()) {
    delay(100);
    lcd.clear();
    while(Serial.available() > 0) {
      lcd.write(Serial.read()); 
    }
  }
}

