#include <Dusk2Dawn.h>
#include <Servo.h>
#include <DS1307RTC.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

Servo servo1; //controls altitude

int Mins=0,Lastmin=0;
int lon, lat, diff,i,r,s,y,m,d;
SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

//conversion of degrees and minutes to decimal degrees
double convertDegMinToDecDeg (float degMin) 
  {
  double min = 0.0;
  double decDeg = 0.0;
 
  min = fmod((double)degMin, 100.0);
 
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg;
}


void setup() 
{
  Serial.begin(115200);
  GPS.begin(9600);
  
   tmElements_t  tm;// specific time

 
  tm.Minute ;
  tm.Hour   ;
  tm.Day    ;
  tm.Month  ;
  tm.Year   ;
  time_t s_date = makeTime(tm);

y = GPS.year;
m = GPS.month;
d = GPS.day;
lon = convertDegMinToDecDeg(GPS.longitude);
lat= convertDegMinToDecDeg(GPS.latitude);
float diff = 5.30;

//calculation of sunrise and sunset as per data from GPS  
  Dusk2Dawn place(lon, lat, diff);
  int placeSunrise  = place.sunrise(y, m, d, false);
  int placeSunset   = place.sunset(y, m , d, false);
  
  char time[6];
  Dusk2Dawn::min2str(time, placeSunrise);
  Serial.println(time); // 06:58

  char time2[] = "00:00";
  Dusk2Dawn::min2str(time2, placeSunset);
  Serial.println(time2); // 16:53


placeSunrise = r;
placeSunset = s;

//daylength = s-r;
// (s-r)/90 ;


  servo1.attach(4);
  servo1.write(180);
  delay(500);

  }
  
  void loop()
{
  tmElements_t tm;
for (i=r;  600<=i<=900 ; i+=5)
{
  if(RTC.read(tm))
  {
 //controlled movement of motor and panel
    Mins = tm.Minute;
    delay(500);
    
    if(Mins==20) servo1.write(6);
    if(Mins==40) servo1.write(12);
    if(Mins==60) servo1.write(18);
    if(Mins==80) servo1.write(24);
    if(Mins==100) servo1.write(30);
    if(Mins==120) servo1.write(36);
    if(Mins==140) servo1.write(42);
    if(Mins==160) servo1.write(48);
    if(Mins==180) servo1.write(54);
    if(Mins==200) servo1.write(60);
    if(Mins==220) servo1.write(66);
    if(Mins==240) servo1.write(72);
    if(Mins==260) servo1.write(78);
    if(Mins==280) servo1.write(84);
    if(Mins==300) servo1.write(90); 
    
    //4 minutes = 1 degree
    if(Mins==320) servo1.write();
    if(Mins==340) servo1.write();
    if(Mins==360) servo1.write();
    if(Mins==380) servo1.write();
    if(Mins==400) servo1.write();   
    if(Mins==420) servo1.write();
    if(Mins==440) servo1.write();
    if(Mins==460) servo1.write();
    if(Mins==480) servo1.write();
    if(Mins==500) servo1.write();   
    if(Mins==520) servo1.write();
    if(Mins==540) servo1.write();
    if(Mins==560) servo1.write();
    if(Mins==580) servo1.write();
    if(Mins==600) servo1.write();   
    if(Mins==620) servo1.write();
    if(Mins==640) servo1.write();
    if(Mins==660) servo1.write();
    if(Mins==680) servo1.write();
    if(Mins==700) servo1.write();
    if(Mins==720) servo1.write(90);
  }
 }
}
