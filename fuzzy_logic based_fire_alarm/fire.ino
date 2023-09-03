#include <dht11.h> // DHT11 kütüphanesini dahil edin

#define DHTPIN 2       // DHT11 sensörünün bağlandığı pin
#define DHTTYPE DHT11  // DHT sensör tipi

#define ALEVPIN A1     // Alev sensörünün bağlandığı analog pin
#define SMOKEPIN A0    // Duman sensörünün bağlandığı analog pin
#define BUZZERPIN 9    // Buzzerın bağlandığı pin

dht11 DHT11;

void setup() {
  Serial.begin(9600);
  pinMode(ALEVPIN, INPUT);
  pinMode(SMOKEPIN, INPUT);
  pinMode(BUZZERPIN, OUTPUT);
}

void loop() {
  int chk = DHT11.read(DHTPIN);

  float temperature = DHT11.temperature; // Sıcaklık ölçümü
  float humidity = DHT11.humidity;       // Nem ölçümü
  int alevValue = analogRead(ALEVPIN);   // Alev sensör değeri okuma
  int smokeValue = analogRead(SMOKEPIN); // Duman sensör değeri okuma

  // Bulanık mantık kuralları ve hesaplamaları
  float temperatureScore = map(constrain(temperature, 0, 90), 0, 90, 0, 1);
  float alevScore = map(constrain(alevValue, 0, 1200), 0, 1200, 1, 0);
  float smokeScore = map(constrain(smokeValue, 0, 500), 0, 500, 0, 1);

  // Bulanık mantık kurallarına göre yangın seviyesi hesaplama
  float fireLevel = 0;

  if (smokeScore <= 0.2) {
    // Duman değeri düşükken
    if (temperatureScore <= 0.2 && alevScore <= 0.5) {
      fireLevel = 0; // Yangın yok
    } else if (temperatureScore <= 0.2 && alevScore > 0.5) {
      fireLevel = 0.5; // Muhtemel yangın
    } else if (temperatureScore <= 0.2 && alevScore > 0.7) {
      fireLevel = 0.7; // Muhtemel yangın
    }
  } else if (smokeScore > 0.2 && smokeScore <= 0.6) {
    // Duman değeri normal
    if (temperatureScore <= 0.2 && alevScore <= 0.5) {
      fireLevel = 0; // Yangın yok
    } else if (temperatureScore <= 0.2 && alevScore > 0.5) {
      fireLevel = 0.5; // Muhtemel yangın
    } else if (temperatureScore <= 0.2 && alevScore > 0.7) {
      fireLevel = 1; // Yangın
    }
  } else if (smokeScore > 0.6) {
    // Duman değeri yüksek
    if (temperatureScore <= 0.2 && alevScore <= 0.5) {
      fireLevel = 0.5; // Muhtemel yangın
    } else if (temperatureScore <= 0.2 && alevScore > 0.5) {
      fireLevel = 1; // Yangın
    } else if (temperatureScore <= 0.2 && alevScore > 0.7) {
      fireLevel = 1; // Yangın
    }
  }

  // Yangın tespiti ve eylemler
  if (fireLevel >= 0.7) {
    Serial.println("Yangın tespit edildi!");
    Serial.print("Sıcaklık: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Nem: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Alev Değeri: "); Serial.println(alevValue);
    Serial.print("Duman Değeri: "); Serial.println(smokeValue);
    Serial.println("-----------------------------");

    digitalWrite(BUZZERPIN, HIGH); // Buzzerı aktifleştir (alarm çal)
    delay(5000); // 5 saniye boyunca alarm çalsın
    digitalWrite(BUZZERPIN, LOW);  // Buzzerı kapat
  }

  delay(10000); // 10 saniye bekleyerek tekrar ölçüm yapalım
}
