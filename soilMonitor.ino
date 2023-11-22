//Arduino Code - 1602LCD Conventional

#include <LiquidCrystal.h>// include the library code
LiquidCrystal lcd(9,10,4,5,6,7);// Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int sensors[] = {A0, A1, A2, A3, A4, A5};

const int sensorMax = 1023;
const int sensorMin = 400;

int sensorVal = 0;

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:   
}

void loop() { 
  sensorTable();
}

void sensorTable(){
  lcd.setCursor(0,0);  // set the cursor to column 0, line 0
  lcd.print("|S1|S2|S3|S4|S5|");
  lcd.setCursor(0,1);  // set the cursor to column 0, line 1
  lcd.print("|");
  for (int analogPin : sensors){
    sensorVal = analogRead(analogPin);
    sensorVal = constrain(sensorVal, sensorMin, sensorMax);
    // convert raw data to percent
    sensorVal = map(sensorVal, sensorMin, sensorMax, 100, 0);
    if (sensorVal < 10){
      lcd.print(" ");
      lcd.print(sensorVal);
    }
    else if (sensorVal >= 100) {
      lcd.print("99");
    }
    else {
      lcd.print(sensorVal);
    }
    lcd.print("|");
  }
  delay(2000);
  lcd.clear();
}