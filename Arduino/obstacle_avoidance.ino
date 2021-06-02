// obstacle avoidance code

#define echo 11
#define trig 12
#define in1 4
#define in2 2
#define enA 3
#define in3 5
#define in4 7
#define enB 6

long duration, distance;
int pos;
#include <Servo.h>

//define servos
Servo servo_top;
Servo servo_left;
Servo servo_right;
// Initialize the integer variables
int num_trash_collected = 0;
int trash_to_becollected=3000;

void setup() {
  
  servo_top.attach(8);
  servo_left.attach(9);
  servo_right.attach(10);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  
}

void loop() {
  
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // echo sent

  duration = pulseIn(echo, HIGH);
  distance = duration / 29.1 / 2;

  if(distance < 15) // onunde cop varsa
  { 
    brakes();
    delay(1000);
    pickup();
    delay(500);
    dropoff();
    num_trash_collected=num_trash_collected+1;
    delay(500);
  }
  goForward();
  if(num_trash_collected==trash_to_becollected){
  empty_bin();
  }
}

void goForward() {
  digitalWrite(in1, HIGH); // move forward for 1.5s
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
  
}

void goBackwards() {
  
  digitalWrite(in1, LOW); // move backward for 1.5s
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
  
}

void goRight() {

  digitalWrite(in1, LOW); // move backward for 1.5s
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
  
}

void brakes() {
  
  digitalWrite(in1, LOW); // stop
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
  
}
void pickup() // bu kolların açıp kapama yapıp çöpü tutması
{
  for(pos = 90; pos < 110; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_top.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  delay(500);
  servo_left.write(0);
  servo_right.write(180);
  delay(1000);
  servo_left.write(75);
  servo_right.write(105);
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
  //servo_top.write(90);
  servo_top.write(0);
  delay(1000);
  servo_left.write(0);//kollar açılsın
  servo_right.write(180);
  delay(1000);
}
void empty_bin()
{
  go_to_trash();// trash alanımız nere olacaksa oraya gitsin bunu nası yapıcaz bilmiyorum tam
  //servo4.write(90); // çöp atma işlemini yapsın
  //servo5.write(90);
  //servo4.write(0);//çöp orijinal pozisyona dönsün
  //servo5.write(0);
  num_trash_collected=0;
}
void go_to_trash()
{
 // amacımız çöpün olduğu yere gitmesi
 // ikinci bir ultrasonik lazım gibi 
}
