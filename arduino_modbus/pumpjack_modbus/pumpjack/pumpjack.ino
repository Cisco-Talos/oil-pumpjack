#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
#include "Mudbus.h"

Mudbus Mb;

int pwm_a = 6;
int dir_a = 7;

int pwm_b = 9;
int dir_b = 12;

int gaugePin=8;
int first_run=true;
int speed_;
int gaugeVal;
Servo gauge; 
int max_speed=15000;
int min_speed=5000;
int default_speed=8000;


void setup() {
  Serial.begin(9600);
  
  uint8_t mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 };
  uint8_t ip[]      = { 10, 10, 10, 1 };
  uint8_t gateway[] = { 10, 10, 10, 1 };
  uint8_t subnet[]  = { 255, 255, 255, 0 };
  Ethernet.begin(mac, ip, gateway, subnet);

  pinMode(pwm_a, OUTPUT);
  pinMode(dir_a, OUTPUT);
  digitalWrite(dir_a, HIGH); 

  //smoke generator
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_b, OUTPUT);
  digitalWrite(dir_b, LOW); 
  analogWrite(pwm_b, 0);
  
  gauge.attach(gaugePin); 

}

void loop(){
  Mb.Run(); 

  //First execution default values
  if (first_run == true)
  {
    Mb.R[6]=default_speed;
    Mb.R[7]=0;
    first_run=false;
  }

  //min & max value
  if(Mb.R[6]>max_speed)
    Mb.R[6]=max_speed;
  if(Mb.R[6]<min_speed)
    Mb.R[6]=min_speed;

  Serial.print("Mb.R[6]: ");
  Serial.println(Mb.R[6]);
  Serial.print("Mb.R[7]: ");
  Serial.println(Mb.R[7]);

  speed_=map(Mb.R[6], min_speed, max_speed, 35, 150);
  Serial.print("Speed: ");
  Serial.println(speed_);
  
  gaugeVal=map(speed_, 35, 150, 0, 250);
  Mb.R[7]=gaugeVal;
  Serial.print("Gauge: ");
  Serial.print(gaugeVal);
  Serial.println(" degrees");
  if (gaugeVal >= 145)
  {
    Serial.println("smoke: on");
    analogWrite(pwm_b, 255);
  } else {
    Serial.println("smoke: off");
    analogWrite(pwm_b, 0);
  }
  

  //set value for real
  analogWrite(pwm_a, speed_);
  gauge.write(180-gaugeVal);

  delay(1000); 
   
}
