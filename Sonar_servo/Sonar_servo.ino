#include <Servo.h>
int trig=A2;
int echo=A1;
Servo turner;
int distance;
int motor1=2,
motor2=3,
motor3=4,
motor4=5;
boolean lefter;
boolean righter;
void setup() {
  // put your setup code here, to run once:
  turner.attach(7);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  int timer=pulseIn(echo,HIGH);
  distance=timer*0.034;
  //Serial.println(distance);
  //delay(200);

  if(lefter==false && righter==false &&distance>=200){
    up();
  }
  else if (distance<150){
    stope();
    look_left();
    if(lefter==true && distance<150){
      look_right();
      lefter=false;
      if(righter=true && distance <150){
        turner.write(90);
        back();
        delay(500);
        turn_check();

      }
      else if(righter=true && distance>=200){
        right();
        delay(500);
        stope();
        delay(50);
        turner.write(90);
        righter=false;
        up();


      }
    }
    else if(lefter=true && distance>200){
      left();
      delay(500);
      stope();
      delay(50);
      lefter=false;
      turner.write(90);
      up();
    } 

  }

}


//////////all functions
void up(){
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,HIGH);
  digitalWrite(motor4,LOW);
}
void stope(){
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,LOW);
}
void back(){
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,HIGH);
}
void left(){
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,HIGH);
  digitalWrite(motor4,LOW);
}
void right(){
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,LOW);
}


///////////servo movement
void look_left(){
  turner.write(0);
  lefter=true;
}
void look_right(){
  turner.write(180);
  righter=true;
}
void turn_check(){
  left();
  delay(500);
  if(distance<150){
    right();
    delay(1000);
    if(distance<150){
      right();
      delay(500);
    }
    else if(distance>=200){
      stope();
      delay(50);
      up();
    }  
  }
  else if(distance>=200){
  stope();
  delay(50);
  up();
  }

}



