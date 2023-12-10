#include <Wire.h>

#include "Adafruit_SHT4x.h"
#include <LiquidCrystal.h>
#include <ezButton.h>

Adafruit_SHT4x sht4 = Adafruit_SHT4x();
LiquidCrystal lcd(9, 10, 4, 5, 6, 7);// Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

const int sensors[] = {A0, A1, A2, A3};
const int noSensors = 4;

const int sensorMax = 1023;
const int sensorMin = 400;

const int leftButtonPin = 11;
const int midButtonPin = 12;
const int rightButtonPin = 13;


ezButton leftButton = ezButton(leftButtonPin);
ezButton midButton = ezButton(midButtonPin);
ezButton rightButton = ezButton(rightButtonPin);

// lcd status
bool lcdOn = true;
int backlightPin = 8;

int sensorVal[] = {1023, 1023, 1023, 1023};

void setup() {
  Wire.begin();
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows

  sht4.begin();
  sht4.setPrecision(SHT4X_HIGH_PRECISION); // highest resolution
  sht4.setHeater(SHT4X_NO_HEATER); // no heater

  leftButton.setDebounceTime(50);
  midButton.setDebounceTime(50);
  rightButton.setDebounceTime(50);

  pinMode(backlightPin, OUTPUT);

}

void loop() { 
  leftButton.loop();
  midButton.loop();
  rightButton.loop();

  if (leftButton.isPressed()) {
    
    sensorTable();
  }

  if (midButton.isPressed()) {
    if (lcdOn){
      lcd.noDisplay();
      digitalWrite(backlightPin, LOW);
      lcdOn = false;
    } else {
      lcd.display();
      digitalWrite(backlightPin, HIGH);
      lcdOn = true;
    }
  }

  if (rightButton.isPressed()) {
    temperatureHumidity();
  }

}

void sensorTable(){
  lcd.clear();

  for (int i = 0; i < noSensors; ++i){
    sensorVal[i] = analogRead(sensors[i]);
    sensorVal[i] = constrain(sensorVal[i], sensorMin, sensorMax);
    // convert raw data to percent
    sensorVal[i]  = map(sensorVal[i], sensorMin, sensorMax, 100, 0);
  }

  // print the vaules
  lcd.setCursor(0,0);
  lcd.print("1: "); lcd.print(sensorVal[0]); lcd.print("%");
  lcd.print("2: "); lcd.print(sensorVal[1]); lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("3: "); lcd.print(sensorVal[2]); lcd.print("%");
  lcd.print("4: "); lcd.print(sensorVal[3]); lcd.print("%");

  lcd.setCursor(0, 0);  // set the cursor to column 0, line 0
  for (int i = 0; i < noSensors; ++i){
    if (i == 2){
      lcd.setCursor(0, 1);  // set the cursor to column 0, line 1
    }
    lcd.print(i + 1); lcd.print(": ");
    if (sensorVal[i] < 10) {
      lcd.print("  ");
    }
    else if (sensorVal[i] < 100){
      lcd.print(" ");
    }
    lcd.print(sensorVal[i]);
    lcd.print("%  ");
  }
}

void temperatureHumidity() {
  lcd.clear();

  sensors_event_t humidity, temp; // temperature and humidity variables
 
  sht4.getEvent(&humidity, &temp);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: "); lcd.print(temp.temperature); lcd.print("\xDF"); lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Humidity: "); lcd.print(humidity.relative_humidity); lcd.print("%");
}