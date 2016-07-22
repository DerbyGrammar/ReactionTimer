/*
  Chris Nethercott
  Reaction Timer
*/

#include <Wire.h> // Wire library for communicating with the I2C devices.
#include <LiquidCrystal_I2C.h>  // LCD library for outputing text to the I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Sets the address for the LCD I2C

const int switchPin = 8; // Switch
const int ledArray[6] = {2,3,4,5,6,7};

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
  
  Serial.begin(9600); // Begins the Serial port for printing with the operator
  
  randomSeed(analogRead(-1)); // You will need this to generate proper 'random' numbers
  
  lcd.begin(); // Begins the LCD
  lcd.backlight(); // Turns on the backlight
  lcdClear();
   
  digitalWrite(switchPin, HIGH); // Writes the switch HIGH, because we use a two prong switch, instead of a push button
}

void lcdClear() {
  lcd.clear(); // Clears the LCD
  lcd.print("Reaction Timer"); // Prints Reaction Timer
}

void pinModes() {
  pinMode(switchPin, INPUT); // Sets switch as an input
  for(int i = 0; i < sizeof(ledArray); i++) {
    pinMode(ledArray[i], OUTPUT);
  }
}

boolean debounce(boolean last) { // To see if the button has been pressed
  boolean current = digitalRead(switchPin); // Sets the boolean to the current state of the button
  if(last != current) { // If the last state does NOT equal current
    delay(5); // Use for stability
    current = digitalRead(switchPin); // Reads the state again, see if it has changed
  }
  return current; // Returns the state of the button
}


void loop() { // Loop runs every milisecond
  currentButton = debounce(lastButton);
  if(lastButton == HIGH && currentButton == LOW) { // When the button was high, but now is low
    Started = !Started; // Toggles the started state
    lastButton = LOW; // Sets the lastButton to low
  }
  
  lastButton = currentButton; // Sets the lastButton state to currentButton
  
  if(Started == true && timer == false) { // When started is true and timer isn't running
    Random(); // Starts the Reaction Timer
    timer = true; // Starts the timer
  }
  if(Started == false && timer == true) { // When started is false and the timer is running
    Stop(); // Stops the Reaction Timer
    timer = false; // Turns off the timer
  } 
}

void Random() {
  randomTime = random(randomTimeMin,randomTimeMax); // Generates the random number
  randomTime = randomTime*1000; // Converts the number from ms to s

  lcdClear();
  digitalWrite(ledPinF, HIGH); // Tells the user that it is ready
  delay(100); // With a small LED blink
  digitalWrite(ledPinF, LOW); // That Turns off
  delay(1000); // Waits a second
  lcd.setCursor(0,1); // Sets the LCD cursor to bottom left
  lcd.print("Get Ready!");
  Serial.print("Random Time: "); // Prints to the operator the randomTime
  Serial.println(randomTime);
  ledSequence(); // Starts the super cool f1 lighting sequence
  delay(randomTime); // Delays the randomTime which was generated earlier
  Start(); // Calls the Start() subroutine
}

void ledSequence() { // LED Sequence 
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
  lcdClear();
  lcd.setCursor(0,1); // Sets the cursor to the second line
  lcd.print("Go!"); // Prints Go!
  startTime = millis(); // Sets the start time using the millis() function.
  allLedsLow(); // Turns all LEDs off
}

void allLedsLow() {
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);
  digitalWrite(ledPinE, LOW);
}

void Stop() {
  endTime = millis(); // Sets the end time
  elapsedTime = (endTime - startTime)+5; // Sets the elasped time to start-end
  elapsedTime = elapsedTime/1000; // Changed it from ms to s
  Serial.print("Reaction Time: "); // Prints to the operator the reaction time
  Serial.println(elapsedTime);
  lcd.clear(); // Clears the LCD
  
  lcd.print("Time: "); // Tells the user their reaction time
  lcd.print(elapsedTime);
  lcd.print("s");
  
  lcd.setCursor(0,1); // Moves the LCD cursor to the second line
  
  if(elapsedTime < 0.2) { // Custom Messages depending on the time
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
  
  allLedsLow(); // Turns all LEDs off
  Serial.println("New User"); // Prints to the operator that there is a new user
}
