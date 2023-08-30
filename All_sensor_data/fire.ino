#include <dht11.h>

int DhtPin = 2;
dht11 dht_sensor;

int alevEsikDegeri = 1000;
int dumanEsikDegeri = 300;
int flameSensorReading;
int smokeSensorReading;
int flameSensorPin = A1;
int smokeSensorPin = A0;
int buzzerPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(smokeSensorPin, INPUT);
}

void loop() {
  int chk = dht_sensor.read(DhtPin);

  Serial.print("Nem Orani (%): ");
  Serial.println((float)dht_sensor.humidity, 2);
  delay(1000);
  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)dht_sensor.temperature, 2);

  flameSensorReading = analogRead(flameSensorPin);
  smokeSensorReading = analogRead(smokeSensorPin);

  if (flameSensorReading < alevEsikDegeri || smokeSensorReading > dumanEsikDegeri) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }

  Serial.print("Flame Sensor reading = ");
  Serial.println(flameSensorReading);

  Serial.print("Smoke Sensor reading = ");
  Serial.println(smokeSensorReading);

  delay(1000);
}
