// obstacle avoidance code


#include <Servo.h>

//define servos
Servo servo_top;
Servo servo_left;
Servo servo_right;
int pos;

void setup() {
  
  servo_top.attach(3);
  servo_left.attach(5);
  servo_right.attach(6);
  
}

void loop() {
  
   delay(500);
   pickup();
   delay(500);
   dropoff();
   delay(500);
}

void pickup() // bu kolların açıp kapama yapıp çöpü tutması
{
  for(pos = 90; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_top.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  delay(500);
  servo_left.write(0);
  servo_right.write(180);
  delay(1000);
  servo_left.write(90);
  servo_right.write(90);
  delay(1000);
  for(pos = 120; pos >= 90; pos -=1)
  {
    servo_top.write(pos);
    delay(15);
  }
  delay(1000);
}
void dropoff() //bu kolların yukarı kalkıp çöpe çöpü bırakması
{
 for(pos = 90; pos > -45; pos -=1)
  {
    servo_top.write(pos);
    delay(15);
  }
  delay(1000);
  servo_left.write(0);//kollar açılsın
  servo_right.write(180);
  delay(1000);
  for(pos = -45; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_top.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  delay(1000);
}
