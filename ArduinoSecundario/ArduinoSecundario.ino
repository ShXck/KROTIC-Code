#include <Servo.h> 

#define LED_R 13
#define LED_G 12
#define LED_B 11
#define LIGHT_PIN 0
 
Servo myservo4; 
Servo myservo3; 
int pos = 0;
double sensorRead = 0;    

void setup() 
{ 
  // serial setup for debugging
  Serial.begin(9600);

  // servos
  myservo4.attach(4);
  myservo3.attach(3);

 // leds 
 pinMode(LED_R, OUTPUT);
 pinMode(LED_G, OUTPUT);
 pinMode(LED_B, OUTPUT);
}
 
void loop() 
{ 
  sensorRead = analogRead(LIGHT_PIN);
  Serial.println("Reading: ");
  Serial.print(sensorRead);
  Serial.println(" ");

  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
  
  for(pos = 0; pos <= 180; pos += 1) 
  {
    myservo4.write(pos);
    myservo3.write(pos);              
    delay(15);                      
  } 

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  
  for(pos = 180; pos>=0; pos-=1)     
  {                                
    myservo4.write(pos);
    myservo3.write(pos);           
    delay(15);                      
  }
}
