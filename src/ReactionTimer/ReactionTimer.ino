/*
  Chris Nethercott
  Reaction Timer
*/

#include <Wire.h> // Wire library for communicating with the I2C devices.
#include <LiquidCrystal_I2C.h>  // LCD library for outputing text to the I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Sets the address for the LCD I2C

const int ledPinA = 2; // Red LED - Red LEDs are used for the sequence
const int ledPinB = 3; // Red LED
const int ledPinC = 4; // Red LED
const int ledPinD = 5; // Red LED
const int ledPinE = 6; // Red LED
const int ledPinF = 7; // Green - For troubleshooting/activating the sequence
const int switchPin = 8; // Switch

int randomTimeMin = 3; // Mininium Time (s)
int randomTimeMax = 8; // Maximium Time (s)
int ledDelayTime = 1000; // Amount of time between the leds coming on

boolean lastButton = LOW;
boolean currentButton = LOW;
boolean Started = false;
boolean timer = false;
long startTime;
long endTime;
long randomTime;
float elapsedTime;

void setup() {
  pinModes();
  
  Serial.begin(9600);
  
  randomSeed(analogRead(-1));
  
  lcd.begin();
  lcd.backlight();
  lcd.print(" Reaction Timer ");
  
  digitalWrite(switchPin, HIGH);
}

void pinModes() {
  pinMode(switchPin, INPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  pinMode(ledPinE, OUTPUT);
  pinMode(ledPinF, OUTPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(switchPin);
  if(last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}


void loop() { 
  currentButton = debounce(lastButton);
  if(lastButton == HIGH && currentButton == LOW) {
    Started = !Started;
    lastButton = LOW;
  }
  
  lastButton = currentButton;
  
  if(Started == true && timer == false) {
    Random();
    timer = true;
  }
  if(Started == false && timer == true) {
    Stop();
    timer = false;
  } 
}

void Random() {
  randomTime = random(randomTimeMin,randomTimeMax);
  randomTime = randomTime*1000;

  lcd.clear();
  lcd.print("Reaction Timer");
  digitalWrite(ledPinF, HIGH);
  delay(100);
  digitalWrite(ledPinF, LOW);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Get Ready!");
  Serial.print("Random Time: ");
  Serial.println(randomTime);
  ledSequence();
  delay(randomTime);
  Start();
}

void ledSequence() {
  digitalWrite(ledPinA, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledPinB, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledPinC, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledPinD, HIGH);
  delay(ledDelayTime);
  digitalWrite(ledPinE, HIGH);
  delay(ledDelayTime);
}

void Start() {
  startTime = millis();
  allLedsLow();
}

void allLedsLow() {
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);
  digitalWrite(ledPinE, LOW);
}

void Stop() {
  endTime = millis();
  elapsedTime = (endTime - startTime)+5;
  elapsedTime = elapsedTime/1000;
  Serial.print("Reaction Timer: ");
  Serial.println(elapsedTime);
  lcd.clear();
  lcd.print("Time: ");
  lcd.print(elapsedTime);
  lcd.print("s");
  
  lcd.setCursor(0,1);
  if(elapsedTime < 0.2) {
    lcd.print("You are fast!");
  }
  else if(elapsedTime < 0.5) {
    lcd.print("Awesome!");
  }
  else if(elapsedTime < 1) {
    lcd.print("Too Slow!");
  }
  else {
    lcd.print("Try Again!");
  }
  
  allLedsLow();   
}
