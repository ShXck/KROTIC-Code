#include <Wire.h>
#include <Servo.h> 

// CONSTANTS
#define SERVO_MOV_TIME 1500
#define BATTERY_TH 460

// ANALOG INPUT
#define TEMPERATURE_PIN 0
#define BATTERY_PIN 1



// STATE LEDS
#define BATTERY_LED 2

// INSTRUCTIONS AVAILABLE
#define READ_LIGHT_INSTR 0
#define READ_TEMP_INSTR 1
#define READ_MOTION_INSTR 2
#define READ_SOUND_INSTR 3
#define MOVE_FORWARD 4
#define MOVE_BACKWARDS 5

Servo servo1;
Servo servo2;

// variable declaration 
int temperature_measure = 0;
int battery_level = 0;
int I2CRead = -1; // instruction read
byte sent_data;
bool isLow;

void setup() {
  // Declares arduino as slave using address 0x8
  Wire.begin(0x8);

  // sets event function handler
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  servo1.attach(9);
  servo2.attach(10);

  servo1.write(90);
  servo2.write(90);
  
  Serial.begin(9600);
  
  pinMode(BATTERY_LED, OUTPUT);
  digitalWrite(BATTERY_LED, LOW);

  isLow = false;
}

void loop() {
  temperature_measure = analogRead(TEMPERATURE_PIN);
  battery_level = analogRead(BATTERY_PIN);

  Serial.println(battery_level);

  sent_data = map(temperature_measure, 0, 1023, 0, 255);

  switch(I2CRead) {
    case READ_LIGHT_INSTR:
    case READ_TEMP_INSTR:
    case READ_MOTION_INSTR:
    case READ_SOUND_INSTR:
      sent_data = map(temperature_measure, 0, 1023, 0, 255);
      I2CRead = -1;
      break;
    case MOVE_FORWARD:
      move_forward();
      I2CRead = -1;
      break;
    case MOVE_BACKWARDS:
      move_backwards();
      I2CRead = -1;
      break;
  }

  if(Serial.available() > 0) {
    char in = Serial.read();
    if(in == '1') {
      stop_movement();
    } else if(in == '2'){
      move_forward();
    } else if(in == '3') {
      move_backwards();
    } else if(in == '4') {
      rotate();
    }
  }

  // warns about low servo battery
  if(battery_level <= BATTERY_TH) {
    if(isLow) {
      digitalWrite(BATTERY_LED, HIGH);
      isLow = false;
    } else {
      digitalWrite(BATTERY_LED, LOW);
      isLow = true;
    }
  }
  
  delay(1000);
}

void move_forward() {
  servo1.write(180);
  servo2.write(0);
  delay(SERVO_MOV_TIME);
  stop_movement();              
}


void move_backwards() {
  servo1.write(0);
  servo2.write(180);
  delay(SERVO_MOV_TIME);
  stop_movement();               
}

void rotate() {
  servo1.write(180);
  servo2.write(180);
  delay(SERVO_MOV_TIME);
  stop_movement();               
}

void stop_movement() {
  servo1.write(90);
  servo2.write(90);              
}

void receiveEvent(int bytes) 
{
  I2CRead = Wire.read();
}

void requestEvent(int bytes) {
  switch(I2CRead) {
    case READ_LIGHT_INSTR:
    case READ_TEMP_INSTR:
    case READ_MOTION_INSTR:
    case READ_SOUND_INSTR:
      Wire.write(sent_data);
      break;
  }
}
