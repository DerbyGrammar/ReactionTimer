/* 
  Chris Nethercott
  Reaction Timer
  v2.0
*/

/* Libraries */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Variables for Pin Numbers */
const int ledA = 2; // Green LED
const int ledB = 3; // Red LED
const int ledC = 4; // Red LED
const int ledD = 5; // Red LED
const int ledE = 6; // Red LED
const int ledF = 7; // Red LED
const int ledG = 8; // Green LED
const int inputButtonA = 9; // Player A
const int inputButtonB = 10; // Player B
const int inputButtonReset = 11; // Reset Button

/* Time Variables */
long randomTime;
long delayTime = 500;
long ledDelayTime = 1000;
int randomTimeMin = 3;
int randomTimeMax = 5;

long startTime;
long currentTime;
long reactionTimeA;
long reactionTimeB;

/* Booleans */
boolean isRunSequence;
boolean isButtonAPressed;
boolean isButtonBPressed;
boolean isButtonResetPressed;

void setup() {
  lcdBegin();
  Serial.begin(9600);
  lcd.print(" Reaction Timer ");
}

void loop() {
  isButtonResetPressed = digitalRead(inputButtonReset);

  if(isButtonResetPressed == HIGH) {
    lcd.clear();
    lcd.print("Starting...");
    isRunSequence = true;
    isButtonAPressed == LOW;
    isButtonBPressed == LOW;
  }

  if(isRunSequence == true) {
    randomGenerator();
    Serial.println(randomTime);
    Serial.println("random generated");
    lcd.clear();
    lcd.print("Get Ready!");
    delay(1000);
    lcd.clear();
    lcd.print("Watch the LEDS!");
    delay(1000);
    lcd.clear();
    ledSequence();
    delay(randomTime);
    startTime = millis();
    allLedsLow();

    isButtonAPressed = digitalRead(inputButtonA);
    isButtonBPressed = digitalRead(inputButtonB);

    if(isButtonAPressed == HIGH || isButtonBPressed == HIGH) {
      Serial.println("Button Pressed");
      currentTime = millis();
      if(isButtonAPressed == HIGH) {
        Serial.println("APRESSED");
        reactionTimeA = currentTime-startTime;
        lcd.print("Player A Wins!");
        lcd.setCursor(0,1);
        lcd.print(reactionTimeA);
        isRunSequence = false;
      }
      if(isButtonBPressed == HIGH) {
        Serial.println("BPRESSED");
        reactionTimeB = currentTime-startTime;
        lcd.print("Player B Wins!");
        lcd.setCursor(0,1);
        lcd.print(reactionTimeB);
        isRunSequence = false;
      } 
    }
  isRunSequence = false; 
  }
}

void lcdBegin() {
  lcd.begin();
  lcd.clear();
}

void randomGenerator() {
  randomSeed(analogRead(-1));
  randomTime = (random(randomTimeMin,randomTimeMax))*1000;
}

void ledSequence() {
  digitalWrite(ledB, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledC, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledD, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledE, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledF, HIGH);
}

void allLedsLow() {
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW);
  digitalWrite(ledE, LOW);
  digitalWrite(ledF, LOW);
}

