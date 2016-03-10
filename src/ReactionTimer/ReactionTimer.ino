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

boolean lastButton = LOW; // If the state of the button has changed
boolean currentButton = LOW; // If the state of the button has changed
boolean Started = false; // If the reaction timer has started
boolean timer = false; // If the timer has started
long startTime; // startTime for measuring the reaction time
long endTime; // endTime for measuring the reaction time
long randomTime; // randomTime delay from all LEDs on to them all off
float elapsedTime; // startTime - endTime

void setup() {
  pinModes(); // Uses a subroutine to set all of the inputs/outputs
  
  Serial.begin(9600); // Begins the Serial port for printing with the operatio
  
  randomSeed(analogRead(-1)); // You will need this to generate proper 'random' numbers
  
  lcd.begin(); // Begins the LCD
  lcd.backlight(); // Turns on the backlight
  lcd.print(" Reaction Timer "); // Prints Reaction Timer, useful in a hard restart
   
  digitalWrite(switchPin, HIGH); // Writes the switch HIGH, because we use a two prong switch, instead of a push button
}

void pinModes() {
  pinMode(switchPin, INPUT); // Sets switch as an input
  pinMode(ledPinA, OUTPUT); // Sets the LEDs as an output
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  pinMode(ledPinE, OUTPUT);
  pinMode(ledPinF, OUTPUT);
}

boolean debounce(boolean last) { // To see if the button has been pressed
  boolean current = digitalRead(switchPin); // Sets the boolean to the current state of the button
  if(last != current) // If the last state does NOT equal current
  {
    delay(5); // Use for stability
    current = digitalRead(switchPin); // Reads the state again, see if it has changed
  }
  return current; // Returns the state of the button
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
