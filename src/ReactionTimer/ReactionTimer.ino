/*
  Chris Nethercott
  Reaction Timer
*/

/* Libraries */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

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

/* Buttons Booleans */
boolean buttonStateA;
boolean buttonStateB;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(" Reaction Timer ");
  Serial.begin(9600);
  randomNumber();
  registerPinModes(); // Calls the function to do it, saves space in setup()
}

void loop() {
  readButtonStates();
  Serial.println(buttonStateA);
  Serial.println(buttonStateB);
}

void randomNumber() {
  randomTime = random(5, 20); //Generates a random number between 5 and 20
  randomTime = randomTime*1000; //Converts that number into secounds. Between 5 seconds and 20
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

void readButtonStates() {
   buttonStateA = digitalRead(inputButtonA);
   buttonStateB = digitalRead(inputButtonB);
}
