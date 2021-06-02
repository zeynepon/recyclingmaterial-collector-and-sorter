#include <Servo.h>

Servo servo_top;
Servo servo_left;
Servo servo_right;

// Initialize the integer variables
int servo_0_angle = 0;
int pos;
 
void setup(){

  // Set the baud rate  
  Serial.begin(9600);
  Serial.println("Connected to Arduino");
  servo_top.attach(8);
  servo_left.attach(9);
  servo_right.attach(10);
   
}
 
void loop(){
  // send default string to RPI to confirm connection
  Serial.println("Connected to Arduino");
 
  if(Serial.available()) {
    servo_0_angle = Serial.parseInt();
    
    pickup();
    dropoff();
  
    Serial.flush();
  }
  delay(1000);
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
