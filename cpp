#include "DHT.h"
#include<LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define DHTPIN 12
#define DHTTYPE DHT11
#define pwm 9

byte degree[8] = {
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.print("   Fan Speed  ");
  lcd.setCursor(0,1);
  lcd.print("  Controlling ");
  delay(2000);
  analogWrite(pwm, 255);
  lcd.clear();
  lcd.print("Robu ");
  delay(2000);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");

  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0,1);

  if(t < 20) {
    analogWrite(pwm, 0);
    lcd.print("Fan OFF            ");
  } else if(t == 20) {
    analogWrite(pwm, 102);
    lcd.print("Fan Speed: 40%   ");
  } else if(t == 26) {
    analogWrite(pwm, 51);
    lcd.print("Fan Speed: 20%   ");
  } else if(t == 28) {
    analogWrite(pwm, 153);
    lcd.print("Fan Speed: 60%   ");
  } else if(t == 29) {
    analogWrite(pwm, 204);
    lcd.print("Fan Speed: 80%    ");
  } else if(t > 29) {
    analogWrite(pwm, 255);
    lcd.print("Fan Speed: 100%   ");
  }
  
  delay(3000);
}
