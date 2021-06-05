// obstacle avoidance code with the addition of serial communication with rpi

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
//Servo servo_cop_right;
//Servo servo_cop_left;
// Initialize the integer variables
int num_metal_collected = 0;
int metal_to_becollected = 3;
int num_plastic_collected = 0;
int plastic_to_becollected = 2;
int num_paper_collected = 0;
int paper_to_becollected = 3;
// Initialize the integer variables
int rpi_input = 0;
int trash_kind = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Connected to Arduino");
  servo_top.attach(8);
  servo_left.attach(9);
  servo_right.attach(10);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  servo_top.write(0);
}

void loop() 
{
  goForward();
  int sensorDegeri = analogRead(A1); // Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // echo sent

  duration = pulseIn(echo, HIGH);
  distance = duration / 29.1 / 2;
  //servo_top.write(0);
  
  // send default string to RPI to confirm connection
  // Serial.println("Connected to Arduino");
  
  if(Serial.available())
  {
    rpi_input = Serial.parseInt();
    delay(2000); // rpiya zaman tanıdık
    
    if(distance < 15) {
      brakes();
      delay(5000);
      if(rpi_input=trash_kind) {
        digitalWrite(LED_BUILTIN, LOW);    
        delay(500); 
        pickup();
        delay(500);
        dropoff();
        if (trash_kind=1) {
          num_metal_collected=num_metal_collected+1;
        }
        else if(trash_kind=2) {
          num_plastic_collected=num_plastic_collected+1;
        }
        else {
          num_paper_collected=num_paper_collected+1;
        }
      }
    }
    goForward();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.println("Done Moving");
    Serial.flush();
   }
   if((num_metal_collected==metal_to_becollected)||(num_plastic_collected==plastic_to_becollected)||(num_paper_collected=paper_to_becollected))
   {
     empty_bin();
     trash_kind=trash_kind+1;
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(500);                       // wait for a second
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(500);                       // wait for a second
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(500);                       // wait for a second
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(500);                       // wait for a second
   }
}

void goForward() 
{
  
  digitalWrite(in1, HIGH); // move forward for 1.5s
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
}

void goBackwards() 
{
  
  digitalWrite(in1, LOW); // move backward for 1.5s
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
  
}

void goRight() 
{

  digitalWrite(in1, LOW); // move backward for 1.5s
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);
  
}

void brakes() 
{
  digitalWrite(in1, LOW); // stop
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
 
}

void pickup() // bu kolların açıp kapama yapıp çöpü tutması
{
  for(pos = 60; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
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
  for(pos = 120; pos >= 60; pos -=1)
  {
    servo_top.write(pos);
    delay(15);
  }
  delay(1000);
}

void dropoff() //bu kolların yukarı kalkıp çöpe çöpü bırakması
{
 for(pos = 60; pos > 0; pos -=1)
  {
    servo_top.write(pos);
    delay(15);
  }
  delay(1000);
  servo_left.write(0);//kollar açılsın
  servo_right.write(180);
  delay(1000);
  for(pos = 0; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_top.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  delay(1000);
}
void empty_bin()
{
  //go_to_trash()
  //servo_cop_right.write(0); //geriye at
  //servo_cop_left.write(180);
  delay(1000);
  //servo_cop_right.write(180); //pozisyona dön
  //servo_cop_left.write(0);
}
void go_to_trash()
{
 // bunu beraber yapalım bu bos amacımız çöpün olduğu yere gitmesi
 // ikinci bir ultrasonik lazım gibi 
}
