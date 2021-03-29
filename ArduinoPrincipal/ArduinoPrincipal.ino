#define TEMPERATURE_PIN 0
#define SOUND_PIN 1
#define MOVEMENT_PIN 2
#define TEMP_PIN 3

double temperature_measure = 0;
double sound_measure = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  temperature_measure = analogRead(TEMPERATURE_PIN);
  sound_measure = analogRead(SOUND_PIN);
  Serial.println("Temp: ");
  Serial.println(temperature_measure);
  Serial.println();
  Serial.println("Sound: ");
  Serial.println(sound_measure);
  Serial.println("----------------");
  delay(1000);
}
