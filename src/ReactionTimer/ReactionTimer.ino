/*
  Chris Nethercott
  Reaction Timer
*/

/* Libraries */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Variables */
const int ledA = 2; // Green LED
const int ledB = 3; // Red LED
const int ledC = 4; // Red LED
const int ledD = 5; // Red LED
const int ledE = 6; // Red LED
const int ledF = 7; // Red LED
const int ledG = 8; // Green LED
const int inputButtonA = 9; // Player A
const int inputButtonB = 10; // Player B
long randomTime; // Storage of the randomTime
int delayTime = 5000;
int ledDelayTime = 1000;
/* Buttons Booleans */
boolean buttonStateA;
boolean buttonStateB;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.print(" Reaction Timer ");
  registerPinModes();
  randomTimeGeneration();
  Serial.print(randomTime);
  Start();
  delay(delayTime);
}

void registerPinModes() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);
  pinMode(ledF, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(inputButtonA, INPUT);
  pinMode(inputButtonB, INPUT);
}

void randomTimeGeneration() {
  randomTime = random(3, 8);
  randomTime = randomTime*1000;
}

void Start() {
  lcd.clear();
  lcd.print("When the lights");
  lcd.setCursor(0,1);
  lcd.print("go off.");
  delay(delayTime);
  lcd.clear();
  lcd.print("Press the button");
  delay(delayTime);
  lcd.clear();
  lcd.print("Lets go!");
  ledSequence();
  delay(randomTime);
  ledAllLow();
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

void ledAllLow() {
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW);
  digitalWrite(ledE, LOW);
  digitalWrite(ledF, LOW);
}

void loop() {
  buttonStateA = digitalRead(inputButtonA);
  buttonStateB = digitalRead(inputButtonB);
}
