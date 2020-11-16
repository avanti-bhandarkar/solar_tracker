#include "RTClib.h"

RTC_DS1307 rtc;

 
// initialize for length of day
int n,c;
int lod , delta , corr;
int rise , set;
int lat = 19.076;//change this for change in latitude, currently set to Mumbai
int lon = 72.877;//change this for change in longitude, currently set to Mumbai
int risehourchange , riseminchange;
int sethourchange , setminchange;
int finalrise, finalset, finallod , change;

//do not change the inst lat or lon when in use for India
int istlat = 25.435;
int istlon =81.846;

// initialize for RTC
int Mins=0,Lastmin=0;
int t, y, m, d; 

//initialize for working of actuator
int givenlongitude , givenlatitude;
int limit1 , limit2;
int i;

//conver dms to decdeg
 double convertDegMinToDecDeg (float degMin) 
  {
  double min = 0.0;
  double decDeg = 0.0;
 
  min = fmod((double)degMin, 100.0);
 
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg; 
  }
  

void setup () {

Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (true);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
 
    rtc.adjust(DateTime((__DATE__), (__TIME__)));
  }
  DateTime now = rtc.now();
    
  t== (now.hour())*60+(now.minute());
  y == now.year() ;
  m == now.month();
  d == now.day();
  givenlongitude == convertDegMinToDecDeg(lon);
  givenlatitude== convertDegMinToDecDeg(lat);
 /*   
    switch (m)
{
    case 1: n = 0 ;
        break;
    case 2: n = 31;
        break;
    case 3: n = 59 ;
        break;
    case 4: n = 90;
        break;
    case 5: n = 120;
        break;
    case 6: n = 151;
        break;
    case 7: n = 181;
        break;
    case 8: n = 212;
        break;
    case 9: n = 243 ;
        break;
    case 10: n = 273;
        break;
    case 11: n = 304;
        break;
    case 12: n = 334;
        break;
}
*/
c = 1+10;

delta = 23.45 * sin (360/365*(284+c));

lod = (2/15)*(acos(-1)*tan(lat)* tan (delta));

corr =(istlon-lon)/4;

rise = (12-(lod/2))+(corr);
set = rise + lod;

//converting sunrise and sunset into hours and mins
risehourchange = trunc(rise);
riseminchange = rise - risehourchange;

sethourchange = trunc(set);
setminchange = rise - sethourchange;

//getting sunrise and sunset times as minutes
finalrise = riseminchange + 60*(risehourchange);
finalset = setminchange + 60*(sethourchange);

//calculating day length in minutes
finallod = finalset - finalrise;

//finding time between each 1 degree step
change = finallod/180;

//limits for motion of solar panel
limit1 = (720 - finalrise)/2 ; // difference bw 12 noon and sunrise time divided by 2
limit2 = (finalset- 720)/2; //12 pm and sunset time difference divided by 2 
  
}

void loop () {
   /* DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(100);*/
    
Serial.print("Latitude of the place");
Serial.print(lat);
Serial.print("\n");
Serial.print("Longitude of the place");
Serial.print(lon);
Serial.print("\n");
delay(100);
Serial.print("Date");
Serial.print(d);
Serial.print("/");
Serial.print(m);
Serial.print("/");
Serial.print(y);
Serial.print("\n");
delay(100);
Serial.print("Angle of declination");
Serial.print(delta);
Serial.print("\n");
Serial.print("Sunrise time ");
Serial.print(rise);
Serial.print("\n");
Serial.print("Sunset time");
Serial.print(set);
Serial.print("\n");
Serial.print("Length of day");
Serial.print(lod);
Serial.print("\n");
delay(100);
Serial.print("Limits of motion for the motor");
Serial.print(limit1);
Serial.print("\n");
Serial.print(limit2);
Serial.print("\n");

}
