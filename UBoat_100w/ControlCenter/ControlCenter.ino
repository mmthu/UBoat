/////////NR2401
#include <SPI.h>  
#include <Mirf.h>  
#include <nRF24L01.h>  
#include <MirfHardwareSpiDriver.h>  
  
int value;

int x=A0,y=A1;  
int valuex=0,valuey=0;

void setup()  
{  
  //SPI to NRF24L01
  Mirf.spi = &MirfHardwareSpi;  
  Mirf.init();  
  Mirf.setRADDR((byte *)"ABCDE"); //设置自己的地址（发送端地址），使用5个字符  
  Mirf.payload = sizeof(value);  
  Mirf.channel = 90;              //设置所用信道  
  Mirf.config();  
  Serial.begin(9600);  
}  
  
void loop()  
{  
  Mirf.setTADDR((byte *)"FGHIJ");           //set the address for receiving signal
  valuex=analogRead(x);
  valuey=analogRead(y);
  Serial.print(value);Serial.println("  ");
  if (valuey<250)
  {
    value=111;//forward
  }
  else if (valuex<250)
  {
    value=222;// turn left
  }
  else if(valuex>750)
  {
    value=444;//turn right
  }
  else
  {
    value=101;//stop
  }
 Serial.print(value);Serial.println("  ");     
 /////////////////////////////////////////////////////////////////////
 //Serial.println(value);
  Mirf.send((byte *)&value);                //send the command 
  while(Mirf.isSending()) delay(1);         //keep sending until success  
  delay(50);  
}  
///////////////////////////////////////////////////////////////////////////////////
