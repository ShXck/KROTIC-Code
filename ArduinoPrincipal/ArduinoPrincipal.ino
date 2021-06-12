#include <Wire.h>
#include <Servo.h> 

// CONSTANTS
#define SERVO_MOV_TIME 1250

// ANALOG INPUTS
#define LIGHT_SENSOR_PIN 0
#define TEMP_SENSOR_PIN 1
#define MOTION_SENSOR_PIN 2
#define SOUND_SENSOR_PIN 3

// INSTRUCTIONS AVAILABLE
#define READ_LIGHT_INSTR 0
#define READ_TEMP_INSTR 1
#define READ_MOTION_INSTR 2
#define READ_SOUND_INSTR 3
#define MOVE_FORWARD 4
#define MOVE_BACKWARDS 5
#define ROTATE_RIGHT 6
#define ROTATE_LEFT 7

Servo servo1;
Servo servo2;

// Analog readings

int temperature_measure = 0; // temperature sensor reading
int light_measure = 0;       // light sensor reading
int motion_measure = 0;      // motion sensor reading
int sound_measure = 0;       // sound sensor reading


// I2C
int I2CRead = -1; // instruction read
byte sent_data;   // data to be sent to the raspberry upon request

void setup() {
  // Declares arduino as slave using address 0x8
  Wire.begin(0x8);

  // sets event function handler
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  // attach servos to digital pins 9 and 10
  servo1.attach(9);
  servo2.attach(10);

  // stop the servos from the begginning
  servo1.write(90);
  servo2.write(90);
  
  Serial.begin(9600);
}

void loop() {
  temperature_measure = analogRead(TEMPERATURE_PIN);
  light_measure = analogRead(READ_LIGHT_INSTR);       
  motion_measure = analogRead(MOTION_SENSOR_PIN);     
  sound_measure = analogRead(SOUND_SENSOR_PIN); 

  switch(I2CRead) {
    case READ_LIGHT_INSTR:
      sent_data = map(light_measure, 0, 1023, 0, 255);        // map it to only send 8 bits.
      I2CRead = -1;
      break;
    case READ_TEMP_INSTR:
      sent_data = map(temperature_measure, 0, 1023, 0, 255); // map it to only send 8 bits.
      I2CRead = -1;
      break;
    case READ_MOTION_INSTR:
      sent_data = map(motion_measure, 0, 1023, 0, 255);      // map it to only send 8 bits.
      I2CRead = -1;
      break;
    case READ_SOUND_INSTR:
      sent_data = map(sound_measure, 0, 1023, 0, 255);       // map it to only send 8 bits.
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
    case ROTATE_RIGHT:
      rotate_right();
      I2CRead = -1;
      break;
    case ROTATE_LEFT:
      rotate_left();
      I2CRead = -1;
      break;
  }

  /**
   * Test purposes only, use the serial monitor to test servo movement.
   */
  if(Serial.available() > 0) {
    char in = Serial.read();
    if(in == '1') {
      stop_movement();
    } else if(in == '2'){
      move_forward();
    } else if(in == '3') {
      move_backwards();
    } else if(in == '4') {
      rotate_right();
    } else if(in == '5'){
      rotate_left();
    }
  }

  // warns about low servo battery
  /*if(battery_level <= BATTERY_TH) {
    if(isLow) {
      digitalWrite(BATTERY_LED, HIGH);
      isLow = false;
    } else {
      digitalWrite(BATTERY_LED, LOW);
      isLow = true;
    }
  }*/
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

void rotate_right() {
  servo1.write(180);
  servo2.write(180);
  delay(225);
  stop_movement();               
}

void rotate_left() {
  servo1.write(0);
  servo2.write(0);
  delay(200);
  stop_movement();               
}

void stop_movement() {
  servo1.write(90);
  servo2.write(90);              
}

/**
 * This function is triggered when the Raspberry sends an instruction.
 */
void receiveEvent(int bytes) 
{
  I2CRead = Wire.read();
}

/**
 * This function is triggered when the Raspberry request the value of a sensor.
 */
void requestEvent(int bytes) 
{
  Wire.write(sent_data); // send requested data.
}
