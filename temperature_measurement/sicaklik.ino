#define LM35 A1
#define K 3
#define Y 2 
float sicaklik;
int deger;

void setup() {
  pinMode(LM35, INPUT);
  pinMode(K, OUTPUT);
  pinMode(Y, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  deger=analogRead(LM35);
  Serial.println(deger);
  sicaklik=(5000.0/1023.0)*deger;
  sicaklik=sicaklik/10.0;
  Serial.print("Sıcaklık: ");
  Serial.print(sicaklik);
  Serial.println(" C |");
  delay(3000);
  if (sicaklik<10)
  {
    digitalWrite(Y, LOW);
    digitalWrite(K, HIGH);
    delay(500);
  }
  if (sicaklik>=20 && sicaklik<30)
  {
    digitalWrite(Y, HIGH);
    digitalWrite(K, LOW);
    delay(500);
  }
  if (sicaklik>30)
  {
    digitalWrite(Y, LOW);
    digitalWrite(K, HIGH);
    delay(500);
  }
}
