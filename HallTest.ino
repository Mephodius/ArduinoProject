#include <Arduino.h>
#include <TM1637Display.h>
#include <Servo.h>
Servo serv;
const int Speed=9600;
unsigned int min_speed=0;  
unsigned int max_speed=40;
const uint8_t wheel_length=2.05;
const uint8_t HALL=10;
const uint8_t CLK=5;
const uint8_t DIO=4;
const uint8_t POWER=3;
const uint8_t POWER1=6;
const uint8_t POWER2=9;
const uint8_t GND=2;
const uint8_t GND1=7;
const uint8_t GND2=12;
const uint8_t SERV=8;
const uint8_t BUT=13;
TM1637Display display(CLK, DIO);
void setup() {
  Serial.begin(Speed);
   Serial.println("hello");
  // put your setup code here, to run once:
   serv.attach(SERV);
  pinMode(HALL, INPUT);
   pinMode(BUT, INPUT);
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);
   pinMode(POWER1, OUTPUT);
  digitalWrite(POWER1, HIGH);
  pinMode(POWER2, OUTPUT);
  digitalWrite(POWER2, HIGH);
   pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
   pinMode(GND1, OUTPUT);
  digitalWrite(GND1, LOW);
   pinMode(GND2, OUTPUT);
  digitalWrite(GND2, LOW);
}
bool mark=true;
bool first=true;
float SPEED=0;
uint32_t lastturn=0;
uint32_t lastbut=0;
float DIST =0;
void loop() {
  display.setBrightness(0x0f);
  if((millis()-lastturn)>2000&&first!=true){
      first=true;
      SPEED=0;
      Serial.print("3");
      Serial.print(" ");
      Serial.print(lastturn);
      Serial.println();
      
    }
  if(digitalRead(HALL)==LOW){
    if(first==true){
      first=false;
      SPEED=0;
      Serial.print("1");
       Serial.print(" ");
      Serial.print(millis());
      Serial.println();
      
    }
    else
    if((millis()-lastturn)>30&&(millis()-lastturn)<=2000){
      DIST=DIST+(float)wheel_length/10; 
      SPEED=wheel_length*1000*3.6/(millis()-lastturn);
      Serial.print("2");
       Serial.print(" ");
      Serial.print(millis()-lastturn);
      Serial.println();
      
  }
       lastturn=millis();
  }
  if(digitalRead(BUT)==HIGH&&millis()-lastbut>500)
  {
    if(mark==true)
  mark=false;
  else
  mark=true;
  lastbut=millis();
  }
  if(mark==true)
  display.showNumberDec((int)SPEED, false);
  if(mark==false)
  display.showNumberDec((int)DIST,true);
  int pos=map(SPEED, min_speed, max_speed, 180, 0); //перевести значение от минимума до максимума в угол поворота сервы (от 0 до 180)
  serv.write(pos);
}
