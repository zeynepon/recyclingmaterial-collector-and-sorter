// obstacle avoidance code

#define echo 11
#define trig 12
#define motorR1 4
#define motorR2 2
#define motorRE 3
#define motorL1 7
#define motorL2 5
#define motorLE 6

long duration, distance;

void setup() {
  
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorRE, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorLE, OUTPUT);
  
}

void loop() {
  
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // echo sent

  duration = pulseIn(echo, HIGH);
  distance = duration / 29.1 / 2;

  if(distance < 15) { 
    goBackwards();
    delay(500);
    goRight();
    delay(500);
    brakes();
  }
  else {
    goForward();
  }
  
}

void goForward() {
  
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorRE, 150);
  
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorLE, 150);
  
}

void goBackwards() {
  
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  digitalWrite(motorRE, 150);
  
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorLE, 150);
  
}

void goRight() {

  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  digitalWrite(motorRE, 150);

  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorLE, 150);
  
}

void brakes() {
  
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorRE, 0);

  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorLE, 0);
  
}
