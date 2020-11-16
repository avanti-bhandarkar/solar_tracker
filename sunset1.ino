#include <RTClib.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <SunSet.h>

#include <Wire.h>
#include <Time.h>
#include <TimeLib.h>
#include <Servo.h>

RTC_DS3231 RTC;

#define button 9
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  false //--------->turned off
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup()  
{
   
  Serial.begin(115200);
  GPS.begin(9600);
  
  

 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

 
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);

  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
  pinMode(button,INPUT_PULLUP);

  
}


SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else 
  {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);  
  }
  
  
  if (GPS.newNMEAreceived()) {
      
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  }


  if (timer > millis())  timer = millis();

static bool second_time_round=false;

  if(!digitalRead(button)){

   

    

}


double convertDegMinToDecDeg (float degMin) 
{
  double min = 0.0;
  double decDeg = 0.0;
 
  //get the minutes, fmod() requires double
  min = fmod((double)degMin, 100.0);
 
  //rebuild coordinates in decimal degrees
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg;
}

//Latitude
GPS.latitude;
convertDegMinToDecDeg(GPS.latitude);
 
//Longitude
GPS.longitude;
convertDegMinToDecDeg(GPS.longitude);

Servo servo1; //controls altitude
Servo servo2; //controls azimuth
int i,r,s,Mins=0,Lastmin=0;

void setup() {


  //sRise = r;
 //sSet = s;
  

 servo1.attach(2);
  servo1.write(180);
  servo2.attach(3);
  servo2.write(180);
  delay(500);


  
}
void loop()
{

  tmElements_t tm;
  for (i= r ; i <= s ; i+=5)
  {
  if(RTC.read(tm))
  {

    Mins = tm.Minute;
    delay(500);
    
    if(Mins==20) servo1.write(5);
    if(Mins==40) servo1.write(10);
    if(Mins==60) servo1.write(15);
    if(Mins==80) servo1.write(20);
    if(Mins==100) servo1.write(25);
    if(Mins==120) servo1.write(30);
    if(Mins==140) servo1.write(35);
    if(Mins==160) servo1.write(40);
    if(Mins==180) servo1.write(45);
    if(Mins==200) servo1.write(50);
    if(Mins==220) servo1.write(55);
    if(Mins==240) servo1.write(60);
    if(Mins==260) servo1.write(65);
    if(Mins==280) servo1.write(70);
    if(Mins==300) servo1.write(75);   
    if(Mins==320) servo1.write(80);
    if(Mins==340) servo1.write(85);
    if(Mins==360) servo1.write(90);
    if(Mins==380) servo1.write(95);
    if(Mins==400) servo1.write(100);   
    if(Mins==420) servo1.write(105);
    if(Mins==440) servo1.write(110);
    if(Mins==460) servo1.write(115);
    if(Mins==480) servo1.write(120);
    if(Mins==500) servo1.write(125);   
    if(Mins==520) servo1.write(130);
    if(Mins==540) servo1.write(135);
    if(Mins==560) servo1.write(140);
    if(Mins==580) servo1.write(145);
    if(Mins==600) servo1.write(150);   
    if(Mins==620) servo1.write(155);
    if(Mins==640) servo1.write(160);
    if(Mins==660) servo1.write(165);
    if(Mins==680) servo1.write(170);
    if(Mins==700) servo1.write(175);
    if(Mins==720) servo1.write(180);
  }
}
}
