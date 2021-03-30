#include <Wire.h>

#define TEMPERATURE_PIN 0 // analog
#define SOUND_PIN 1 // analog
#define MOVEMENT_PIN 2 // digital
#define TIMER_PIN 3
#define PIR_LED 13 // digital

// variable declaration 
double temperature_measure = 0;
double sound_measure = 0;
int movement_sensor_state = LOW;
int movement_measure = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(MOVEMENT_PIN, INPUT);
  pinMode(PIR_LED, OUTPUT);
}

void loop() {

  temperature_measure = analogRead(TEMPERATURE_PIN);
  sound_measure = analogRead(SOUND_PIN);
  movement_measure = digitalRead(MOVEMENT_PIN);

  if(movement_measure == HIGH) {
    digitalWrite(PIR_LED, HIGH);
    if(movement_sensor_state == LOW) {      
      Serial.println("Motion detected...");
      movement_sensor_state = HIGH;
      // I2C Transmission test
      Wire.beginTransmission(9); // to slave addr = 9
      Wire.write(movement_sensor_state);              
      Wire.endTransmission();
      // end of test
    }
  } else {
    digitalWrite(PIR_LED, LOW);
    if(movement_sensor_state == HIGH) {
      Serial.println("Motion ended...");
      movement_sensor_state = LOW;
      // I2C Transmission test
      Wire.beginTransmission(9); // to slave addr = 9
      Wire.write(movement_sensor_state);              
      Wire.endTransmission();
      // end of test
    }
  }
  
  /*Serial.println("Temp: ");
  Serial.println(temperature_measure);
  Serial.println();
  Serial.println("Sound: ");
  Serial.println(sound_measure);
  Serial.println("----------------");
  delay(1000);*/
}
