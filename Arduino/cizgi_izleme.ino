#define sensor 8

void setup() {

  pinMode(sensor, INPUT);
  Serial.begin(9600);  //Seri haberleşmeyi başlatıyoruz.
  Serial.println("Cizgi Sensoru Testi");
  delay(2000);
}

void loop() {
  Serial.print(digitalRead(sensor));
  delay(100);
}
