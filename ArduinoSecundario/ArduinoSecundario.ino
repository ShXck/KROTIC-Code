#include <Servo.h> 
#include <Wire.h>

// STATE LEDS
#define ARDUINO_LED 13
#define BATTERY_LED 12

// SERVOS
#define SERVO_1_PIN 6
#define SERVO_2_PIN 5

// SENSOR INPUT
#define LIGHT_SENSOR_PIN 0

// INSTRUCTION AVAILABLE
#define READ_LIGHT_SENSOR_INSTR 0
#define MOVE_FORWARD 1
#define MOVE_BACKWARDS 2
 

Servo servo1; 
Servo servo2; 

// VARIABLE DECLARATION
int pos = 0; // Servo position
double light_sensor_measure = 0;  // light sensor input
int I2CRead = -1;  // instruction from I2C Master

void setup() 
{
    // serial setup for debugging
   Serial.begin(9600);
  
    // servos
   servo1.attach(SERVO_1_PIN);
   servo2.attach(SERVO_2_PIN);

   // Declares arduino as slave using address 0xB
   Wire.begin(0xB); 
   Wire.onReceive(receiveEvent);
   Wire.onRequest(requestEvent);

   // leds 
   pinMode(ARDUINO_LED, OUTPUT);
   pinMode(BATTERY_LED, OUTPUT);
}
 
void loop() 
{ 
  light_sensor_measure = analogRead(LIGHT_SENSOR_PIN);

  switch(I2CRead) {
    case READ_LIGHT_SENSOR_INSTR:
      digitalWrite(ARDUINO_LED, HIGH);
      break;
    case MOVE_FORWARD:
      move_forward();
      break;
    case MOVE_BACKWARDS:
      move_backwards();
      break;
  }

  // if movement is finished reset I2C reading variable.
  if(I2CRead != -1) {
    I2CRead = -1;
  }
}

void receiveEvent(int bytes) 
{
  I2CRead = Wire.read();
}

void requestEvent(int bytes) {
    switch(I2CRead) {
    case READ_LIGHT_SENSOR_INSTR:
      // send it over to master
      break;
  }
}

void move_forward() {
  for(pos = 0; pos <= 180; pos += 1) 
  {
    servo1.write(pos);
    servo2.write(pos);              
    delay(15);                      
  } 
}

void move_backwards() {
  for(pos = 180; pos>=0; pos-=1)     
  {                                
    servo1.write(pos);
    servo2.write(pos);           
    delay(15);                      
  }
}
