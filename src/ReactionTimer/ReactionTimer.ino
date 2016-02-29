#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int switchPin = 2;
int ledPin = 12;
int randomTimeMin = 3;
int randomTimeMax = 5;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean Started = false;
boolean timer = false;
long startTime;
long endTime;
long randomTime;
float elapsedTime;

void setup()
{
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(-1));
  lcd.begin();
  lcd.backlight();
  lcd.print(" Reaction Timer ");
  digitalWrite(switchPin, HIGH);
}
<<<<<<< HEAD

void loop() {
  isButtonResetPressed = digitalRead(inputButtonReset);
  isButtonAPressed = digitalRead(inputButtonA);
  isButtonBPressed = digitalRead(inputButtonB);

  if(isButtonResetPressed == HIGH) {
    lcd.clear();
    lcd.print("Starting...");
    isRunSequence = true;
    isButtonAPressed == LOW;
    isButtonBPressed == LOW;
=======
boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  if(last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
>>>>>>> origin/master
  }
  return current;
}

<<<<<<< HEAD
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
=======

void loop()
{
  currentButton = debounce(lastButton);
  if(lastButton == HIGH && currentButton == LOW)
  {
    Started = !Started;
    lastButton = LOW;
>>>>>>> origin/master
  }
  lastButton = currentButton;
  if(Started == true && timer == false)
  {
    Random();
    timer = true;
  }
  if(Started == false && timer == true)
  {
    Stop();
    timer = false;
  }
 
}
void Random()
{
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


void Start(){
  startTime = millis();
  digitalWrite(ledPin, HIGH);
}

void Stop(){
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
