#include <Wire.h>

#include "Adafruit_SHT4x.h"
#include <LiquidCrystal.h>// include the library code

Adafruit_SHT4x sht4 = Adafruit_SHT4x();
LiquidCrystal lcd(9, 10, 4, 5, 6, 7);// Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

const int sensors[] = {A0, A1, A2, A3};
const int noSensors = 4;

const int sensorMax = 1023;
const int sensorMin = 400;

int sensorVal[] = {1023, 1023, 1023, 1023};

void setup() {
  Wire.begin();
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows

  sht4.begin();
  sht4.setPrecision(SHT4X_HIGH_PRECISION); // highest resolution
  sht4.setHeater(SHT4X_NO_HEATER); // no heater
}

void loop() { 
  // temperature_humidity();
  sensorTable();
}

void sensorTable(){

  for (int i = 0; i < noSensors; ++i){
    sensorVal[i] = analogRead(sensors[i]);
    sensorVal[i] = constrain(sensorVal[i], sensorMin, sensorMax);
    // convert raw data to percent
    sensorVal[i]  = map(sensorVal[i], sensorMin, sensorMax, 100, 0);
  }

  // print the vaules
  lcd.print("1: "); lcd.print(sensorVal[0]); lcd.print("%");
  lcd.print("2: "); lcd.print(sensorVal[1]); lcd.print("%");

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



  delay(5000);
  lcd.clear();
}

void temperature_humidity() {
  sensors_event_t humidity, temp; // temperature and humidity variables
 
  sht4.getEvent(&humidity, &temp);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: "); lcd.print(temp.temperature); lcd.print("\xDF"); lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Humidity: "); lcd.print(humidity.relative_humidity); lcd.print("%");
 
  delay(5000);
  lcd.clear();
}