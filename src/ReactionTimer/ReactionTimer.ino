#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int switchPin = 2;
const int ledPin = 12;
int randomTimeMin = 5;
int randomTimeMax = 20;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean Started = false;
boolean timer = false;
long startTime;
long endTime;
long randomTime;
float elapsedTime;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(-1));
  lcd.begin();
  lcd.backlight();
  lcd.print(" Reaction Timer ");
  digitalWrite(switchPin, HIGH);
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
  lcd.print(" Reaction Timer");
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Get Ready!");
  Serial.print("Random Time: ");
  Serial.println(randomTime);
  delay(randomTime);
  Start();
}


void Start() {
  startTime = millis();
  digitalWrite(ledPin, HIGH);
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
  lcd.print("ms");
  lcd.setCursor(0,1);
  if(elapsedTime < 0.5) {
    lcd.print("You are fast!");
  }
  else if(elapsedTime < 2.0) {
    lcd.print("Awesome!");
  }
  else if(elapsedTime < 10.0) {
    lcd.print("Too Slow!");
  }
  else {
    lcd.print("Loser!");
  }
  digitalWrite(ledPin, LOW);
   
}
