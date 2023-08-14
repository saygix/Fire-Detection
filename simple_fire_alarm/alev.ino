int flameSensorPin = A0;
int flameSensorReading;
int buzzerPin = 8;

void setup(void) {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop(void) {
  flameSensorReading = analogRead(flameSensorPin);

  // Eşik değeri sensör okumasını sınırlamak için kullanılıyor
  // Gün ışığında problem çıkarsa eşik değerini düşürmeyi unutmayalıım.
  int threshold = 900;  // Bu değeri ihtiyaca göre ayarlayabilirsiniz

  if (flameSensorReading < threshold) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  Serial.print("Analog reading = ");
  Serial.println(flameSensorReading);

  delay(1000);
}
