#include <Servo.h>
Servo serv;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  serv.attach(5);
  Serial.begin(9600);
  for(int i=6;i<10;i++){
      pinMode(i,OUTPUT);
  }
  serv.write(90);
  start();
}

void start()
{
  digitalWrite(6,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  delay(30);
  Serial.print("Start\n");
}

void stop()
{
  digitalWrite(6,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(9,LOW);
  delay(50);
}

void left()
{
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  delay(30);
}

void right()
{
  digitalWrite(6,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  delay(30);
}

void back()
{
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(30);
}

int pos = 0;
int trigPin=4;
int echoPin=3;
int dist=0;
int distance=0;
long duration=0;
int turnTime=1500;
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  // Serial.print(duration);
  distance=duration*0.034/2;
  return distance;
}
void loop() {
  start();
  delay(50);
  dist=calculateDistance();
  if(dist<20)
  {
    stop();
    delay(1000);
    // delay(1000);
    serv.write(0);
    delay(500);
    int leftDist=calculateDistance();
    delay(10);
    serv.write(180);
    delay(500);
    int rightDist=calculateDistance();
    delay(10);
    serv.write(90);
    delay(500);
    
    if(leftDist>rightDist && leftDist>=20)
    {
      left();
      delay(turnTime);
    }
    else if(rightDist>leftDist && rightDist>=20)
    {
      right();
      delay(turnTime);
    }
    else 
    {
      back();
      delay(turnTime);
    }
  }


}
