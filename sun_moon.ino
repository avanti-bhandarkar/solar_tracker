#include <RTClib.h>


RTC_DS3231 RTC;

#include <sunMoon.h>

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>


int r,i,s;

#define OUR_latitude   GPS.latitude          
#define OUR_longtitude GPS.longitude
#define OUR_timezone   330                    // localtime with UTC difference in minutes

sunMoon  sm;

void printDate(time_t date) {
  char buff[20];
  sprintf(buff, "%2d-%02d-%4d %02d:%02d:%02d",
  day(date), month(date), year(date), hour(date), minute(date), second(date));
  Serial.print(buff);
}

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int days_string_length =12;

//end of clock stuff

#include <Time.h>
#include <TimeLib.h>
#include <Servo.h>

//for button
#define button 9

// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

void setup()  
{
    
  
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  
  //setup button
  pinMode(button,INPUT_PULLUP);

  tmElements_t  tm;                             // specific time

  tm.Second = 0;
  tm.Minute = 12;
  tm.Hour   = 12;
  tm.Day    = 3;
  tm.Month  = 8;
  tm.Year   = 2016 - 1970;
  time_t s_date = makeTime(tm);
  
 
  Serial.begin(9600);
  if (timeStatus() != timeSet) 
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");
  sm.init(OUR_timezone, OUR_latitude, OUR_longtitude);

 
  
  uint32_t jDay = sm.julianDay();               // Optional call
  byte mDay = sm.moonDay();
  time_t sRise = sm.sunRise();
  time_t sSet  = sm.sunSet();
  
sRise = r;
sSet = s;

  

  
}
