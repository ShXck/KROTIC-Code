#include <Wire.h>

// ANALOG INPUT
#define TEMPERATURE_PIN 0 
#define SOUND_PIN 1 
#define MOTION_PIN 2 

// TIMER
#define TIMER_PIN 3

// STATE LEDS
#define ARDUINO_LED 13
#define BATTERY_LED 12
#define SOUND_OUT_PIN 11

// INSTRUCTIONS AVAILABLE
#define READ_TEMP_INSTR 0
#define READ_SOUND_INSTR 1

// variable declaration 
double temperature_measure = 0;
double sound_measure = 0;
int I2CRead = -1; // instruction read  

void setup() {
  // Declares arduino as slave using address 0xA
  Wire.begin(0xA);

  // sets event function handler
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
   
  Serial.begin(9600);
  
  pinMode(ARDUINO_LED, OUTPUT);
  pinMode(BATTERY_LED, OUTPUT);
  pinMode(SOUND_OUT_PIN, OUTPUT);
}

void loop() {
  temperature_measure = analogRead(TEMPERATURE_PIN);
  sound_measure = analogRead(SOUND_PIN);

  if(I2CRead == READ_TEMP_INSTR) {
    digitalWrite(BATTERY_LED, HIGH);
  }
}

void receiveEvent(int bytes) 
{
  I2CRead = Wire.read();
}

void requestEvent(int bytes) {
  switch(I2CRead) {
    case READ_TEMP_INSTR:
      // send it over to master
      break;
    case READ_SOUND_INSTR:     
      // send it over to master
      break;
  }
}
