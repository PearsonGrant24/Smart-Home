#include <SoftwareSerial.h>
SoftwareSerial bt(8, 9); // RX, TX output connections

#include <LiquidCrystal.h> 
#include "dht.h"
#define dataPin A0
#define motor 2
dht DHT;

int temp;
int hum;
int led1 = 3;
int led2 = 4; 
int led3 = 5;
int CloseDoorMotor = 7;
int fanMotor = 6;
int shedMotor = 12;
int chr = 0;

void setup() {
 
 Serial.begin(9600); 
 bt.begin(9600); 
 Serial.println("Ready");
 pinMode(led1,OUTPUT); // Use onboard LED if required.
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(motor, OUTPUT);
 pinMode(shedMotor, OUTPUT);
 pinMode(fanMotor, OUTPUT);
 pinMode(CloseDoorMotor, OUTPUT);
 //digitalWrite(motor, HIGH); 
}

void loop(){
  int readData = DHT.read11(dataPin);
//----------temperature-andHumidity------------------
  hum = DHT.humidity;
  temp = DHT.temperature;
    
  bt.print(temp); //send distance to MIT App
  Serial.print(temp);
  bt.print(";");
  bt.print(hum); //send distance to MIT App 
  bt.println(";");
  
   if(hum > 70)
       {        
       digitalWrite(fanMotor, HIGH);              
       } 
       else if (hum < 69)
       {
        digitalWrite(fanMotor, LOW); 
       }    
//--------lights-----------------------------------------       
  if(bt.available())
    { 
      chr =  bt.read();
     // Serial.println("CONNECTION ESTABLISHED");     
       
      if(chr=='1')
      {        
       // digitalWrite(led1, HIGH);
        analogWrite(led1, chr);
       }     
      else if(chr=='0')
       {               
     //   Serial.println("OFF"); 
        digitalWrite(led1,LOW);                        
       }                
      else if(chr=='3')
       {               
        digitalWrite(led2,HIGH);                                
       } 
      else if(chr=='4')
       {            
        digitalWrite(led2,LOW);                        
        }   
        else if(chr=='5')
       {               
        digitalWrite(led3,HIGH);                                
       } 
      else if(chr=='6')
       {            
        digitalWrite(led3,LOW);                        
        }   
        //*****************All lights here***********************
      else if(chr=='L')
       {            
        digitalWrite(led1,HIGH); 
        digitalWrite(led2,HIGH);     
        digitalWrite(led3,HIGH);                  
        } 
      else if(chr=='Z')
       {       
        digitalWrite(led1,LOW);      
        digitalWrite(led2,LOW);      
        digitalWrite(led3,LOW);                        
        }         
        //**************Shut down********************************
       else if(chr=='X')
       {       
        digitalWrite(led1,LOW);      
        digitalWrite(led2,LOW);      
        digitalWrite(led3,LOW);      
        digitalWrite(motor, HIGH); 
        delay(1000);
        digitalWrite(motor, LOW);    
        digitalWrite(fanMotor, LOW);               
        }         
//-------------motors---------------------------------------
        if(chr=='7')
      {        
       digitalWrite(motor, HIGH);
       delay(1000);
       digitalWrite(motor, LOW);
      // delay(10000);
      // digitalWrite(CloseDoorMotor, HIGH); 
       }     
      else if(chr=='8')
       {               
       digitalWrite(CloseDoorMotor, HIGH); 
       delay(1000);
       digitalWrite(CloseDoorMotor, LOW);                     
       }  
      else if(chr=='9')
       {               
       digitalWrite(shedMotor, HIGH);
       delay(1000);
       digitalWrite(shedMotor, LOW);                          
       }
       else if(chr=='a')
       {               
       digitalWrite(shedMotor, LOW);                        
       } 
       else if(chr=='Y')
       {               
       digitalWrite(fanMotor, HIGH);  
                             
       }
       else if(chr=='M')
       {               
       digitalWrite(fanMotor, LOW);                        
       }     
      }
  delay(1000);
}
