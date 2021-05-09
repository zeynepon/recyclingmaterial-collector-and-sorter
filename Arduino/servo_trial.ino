#include <Servo.h>

Servo mg9951;
Servo mg9952;

void setup() {
  mg9952.attach(8);
  mg9951.attach(9);
}

int p = 0;
void loop() {
  straight();
  delay(2000);
  up();
  delay(2000);
}

void straight() {
  mg9952.write(180);
  mg9951.write(0);
}

void up() {
  mg9952.write(90);
  mg9951.write(90);
}
