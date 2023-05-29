
#include <LiquidCrystal.h>
#include "DHTesp.h"

LiquidCrystal lcd(19, 23, 18, 17, 16, 2);
const int DHT_PIN = 15;

DHTesp dhtSensor;

#define IR_Sensor 22

// Ultrasonic
#define TRIG_PIN 33
#define ECHO_PIN 32

float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  pinMode(IR_Sensor, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  lcd.print("Temp: " + String(data.temperature, 2) + "deg C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(data.humidity, 1) + "per");
  
  delay(1000);

  // Smoke Detection
  int IR=digitalRead(IR_Sensor);  /*digital read function to check IR pin status*/
  if(IR==LOW){               /*If sensor detect any reflected ray*/
        Serial.println("Smoke is detected");   /*LED will turn ON*/
   }

  else if(IR==HIGH) {
       Serial.println("Smoke not detected");
  } 
  else {
     // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  if(distance_cm >= 100) {
     Serial.println("SOmeone is there");
  }

  delay(500);
  }

}



