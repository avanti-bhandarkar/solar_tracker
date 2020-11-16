#include "RTClib.h"
#include "math.h"
RTC_DS1307 rtc;
 float lodd;
// initialize for length of day
float n,result;
float lod, delta , rad = (3.14/180) ,deg = (180/3.14) ,corr;
float rise , sset;
float lat = 19.076;//change this for change in latitude, currently set to Mumbai
float lon = 72.877;//change this for change in longitude, currently set to Mumbai
float risehourchange , riseminchange;
float sethourchange , setminchange;
float finalrise, finalset, finallod , change;

//do not change the inst lat or lon when in use for India
int istlat = 25.435;
int istlon =81.846;

// initialize for RTC
int Mins=0,Lastmin=0;
int t, y, m, d,h,mi,s; 

//initialize for working of actuator
int givenlongitude , givenlatitude ,londiff;
int limit1 , limit2;
int i;

//convert dms to decdeg
 double convertDegMinToDecDeg (float degMin) 
  {
  double min = 0.0;
  double decDeg = 0.0;
 
  min = fmod((double)degMin, 100.0);
 
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg; 
  }
  
int calculateDayOfYear(int d, int m, int y) {
  
  
  int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  
  int doy = 0;
  for (int i = 0; i < m - 1; i++) {
    doy += daysInMonth[i];
  }
  
  doy += d;
  return doy;
}
void setup () 
{
Serial.begin(9600);
}

void loop () 
{

if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (true);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
 
    rtc.adjust(DateTime((__DATE__), (__TIME__)));
  }
  
  DateTime now = rtc.now();
    
  t=now.hour()*60 + now.minute();
  h= now.hour();
  mi = now.minute();
  y = now.year() ;
  m = now.month();
  d = now.day();
  s=now.second();
  givenlongitude = convertDegMinToDecDeg(lon);
  givenlatitude = convertDegMinToDecDeg(lat);
  result = calculateDayOfYear(now.day(),now.month(),now.year());

delta = 23.45 * (sin((360*(284 + result))/365));

lod = 120*deg*(acos(((-1)*(tan(lat*rad))*(tan(delta)))))/15;

//(2*acos((-1*(tan(lat*180/3.14) * tan(delta*180/3.14))/15)));

londiff = istlon-lon;
corr = (londiff)*4;
lodd = 2.1*(sset + (3.5) -(rise-2.5));
rise = (720 + (12-(lod/2))+(corr))/60;
sset = (1440 - (rise + lod))/60;

//converting sunrise and sunset into hours and mins
risehourchange = trunc(rise);
riseminchange = (rise) - risehourchange;

sethourchange = trunc(sset);
setminchange = (sset) - sethourchange;

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
  
  
Serial.print("Latitude of the place:");
Serial.print(lat);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Longitude of the place:");
Serial.print(lon);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Date:");
Serial.print(d);
Serial.print("/");
Serial.print(m);
Serial.print("/");
Serial.print(y);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Time:");
Serial.print(h);
Serial.print(":");
Serial.print(mi);
Serial.print(":");
Serial.print(s);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Cumulative days :");  
Serial.print(result);  
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Angle of declination: ");
Serial.print(delta);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Sunrise time: ");
Serial.print(rise-2.5);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Sunset time: ");
Serial.print(sset+3.5);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Length of day: ");
Serial.print(lodd);
Serial.print("\n");
Serial.print("************************************************");
Serial.print("\n");
delay(1000);
Serial.print("Limits of motion for the actuator");
Serial.print("\n");
Serial.print(rise);
Serial.print("\n");
Serial.print(sset);
Serial.print("\n");
delay(3000);
}
