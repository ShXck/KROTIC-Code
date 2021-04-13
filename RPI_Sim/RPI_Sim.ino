#include <Wire.h>

#define MAIN_SLAVE 0xA
#define SECONDARY_SLAVE 0xB

// MAIN SLAVE COMMANDS
#define READ_TEMP_CMD 0

// SECONDARY SLAVE COMMANDS
#define READ_LIGHT_CMD 0
#define MOVE_FORWARD 1
#define MOVE_BACKWARDS 2

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(MAIN_SLAVE); 
  Wire.write(READ_TEMP_CMD);              
  Wire.endTransmission();

  delay(500);

  Wire.beginTransmission(SECONDARY_SLAVE);
  Wire.write(READ_LIGHT_CMD);              
  Wire.endTransmission();

  delay(500);

  /*Wire.beginTransmission(SECONDARY_SLAVE);
  Wire.write(MOVE_FORWARD);              
  Wire.endTransmission();

  delay(10000);*/
}
