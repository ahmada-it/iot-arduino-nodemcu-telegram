#include<SoftwareSerial.h>
#include<timer.h>

// ultrasonic
#define trigPin A1
#define echoPin A0
long duration, cm, meter;

#define pompa 7 // pin pompa
#define led 13 // pin led
#define buzzer 4 // pin buzzer
int kondisiBuzzer = 1;

SoftwareSerial ss(2,3); // 3 to pin D6 NodeMCU, 2 to pin D5 NodeMCU
auto timer = timer_create_default();

void setup(){
  Serial.begin(9600);
  ss.begin(115200);
  timer.every(1000, sendData);
  timer.every(1000, srf);
  timer.every(100, sanyo);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pompa, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  timer.tick();
}

// fungsi untuk ultrasonik
void srf(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2)/29.1;
  meter = cm/100;
  
  Serial.print(meter);
  Serial.print("m, ");
  Serial.print(cm);
  Serial.print("cm");
  if(cm<=5){
    Serial.print(" -> Pompa Mati, ");
    Serial.println("Led Mati!");
  }
  else{
    Serial.print(" -> Pompa Menyala, ");
    Serial.println("Led Menyala!");
  }
  delay(1000);
}

long getCm(){
  long readCm = cm;
  return readCm;
}

// fungsi bip
void bip(){
  digitalWrite(4,HIGH);
  delay(100);
  digitalWrite(4,LOW);
  Serial.println("Buzzer Menyala!");
}

// fungsi sanyo
void sanyo(){
  if(cm<=5){
    digitalWrite(pompa, HIGH);
    digitalWrite(led, LOW);
    if(kondisiBuzzer==0){
      bip(); // bunyi bip pada buzzer
      kondisiBuzzer=1;
    }
  }
  else{
    digitalWrite(pompa, LOW);
    digitalWrite(led, HIGH);
    if(kondisiBuzzer==1){
      bip(); // bunyi bip pada buzzer
      kondisiBuzzer=0;
    }
  }
}

void sendData(){
  String msg = "@";
  msg += String(getCm());

  ss.println(msg);
}
