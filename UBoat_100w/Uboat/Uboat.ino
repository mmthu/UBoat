#include <SPI.h>  
#include <Mirf.h>  
#include <nRF24L01.h>  
#include <MirfHardwareSpiDriver.h> 
#include <Servo.h>
#include <Wire.h>
#include <JY901.h>

Servo myservo;
int value,flag=0;  
float anglex=0;
void setup()  
{  
  Mirf.spi = &MirfHardwareSpi;  
  Mirf.init();     
  Mirf.setRADDR((byte *)"FGHIJ"); 
  Mirf.payload = sizeof(value);     
  Mirf.channel = 90; 
  Mirf.config();   
 //  JY901.StartIIC();
 //servo motor initialization
  myservo.attach(3);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  analogWrite(5,76);
  analogWrite(6,76);
  delay(50);
  Serial.begin(9600);  
}  
  
void loop()  
{  
  //JY901.GetAngle();
  anglex=(float)JY901.stcAngle.Angle[0]/32768*180;
 // Serial.println(anglex);
  if (abs(anglex)<40)
  {
    flag=0;
    myservo.write(0);
    delay(50);
  } 
  else if (abs(anglex)>140)
  {
    flag=1;
    myservo.write(180);
    delay(50);
  }
  else
  {
    delay(5);
  } 
//Manual control  
  if(Mirf.dataReady()) 
  {
    Mirf.getData((byte *) &value);  
    //Serial.print("Direction code:  ");
    Serial.println(value);  
    //forward,leftturn,rightturn,stop
    //mid speed：51;high speed 61
    if(value==111) //forward
    {
        analogWrite(5,61);
        analogWrite(6,61);   
    }
    else if(value==222)//left
    {
      if(flag==0)
      {
        analogWrite(5,61);
        analogWrite(6,76);
      }
       else
      {
        analogWrite(5,76);
        analogWrite(6,61);
      }
    }
    else if(value==444)//right
    {
      if(flag==0)
      {
        analogWrite(5,76);
        analogWrite(6,61);
      }
      else
      {
        analogWrite(5,61);
        analogWrite(6,76);
      }
    }
    else //stop
    {
      analogWrite(5,76);
      analogWrite(6,76);
    } 
  }
}  

void serialEvent() 
{
  while (Serial.available()) 
  {
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
  }
}
