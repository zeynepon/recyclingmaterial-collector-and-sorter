#include <Servo.h>

//define servos
Servo servo_cop_right;
Servo servo_cop_left;

void setup(){
  servo_cop_right.attach(3);
  servo_cop_left.attach(5);
}

void loop(){
  empty_bin();
  delay(500);
}
void empty_bin() 
{
  servo_cop_right.write(360); //geriye at
  //servo_cop_left.write(180);
  delay(3000);
  servo_cop_right.write(0); //pozisyona dön
  //servo_cop_left.write(0);
  

}
