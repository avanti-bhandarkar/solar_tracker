  #include <Dusk2Dawn.h>
  #include <Servo.h>
  #include <DS1307RTC.h>


  Servo servo1; //controls altitude

  int Mins=0,Lastmin=0;
  int lon, lat, diff,t,i,r,s,y,m,d;
  const int forwards = 7;
  const int backwards = 6;


  float givenlatitude = 19.076; //change this to change latitude
  float givenlongitude = 72.877;//change this to change longitude

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
  
  pinMode(forwards, OUTPUT);//set relay as an output
  pinMode(backwards, OUTPUT);//set relay as an output

  tmElements_t  tm;// specific time from RTC is initialized

 
  tm.Minute ;
  tm.Hour   ;
  tm.Day    ;
  tm.Month  ;
  tm.Year   ;
  time_t s_date = makeTime(tm);

  t= (tm.Hour)*60+(tm.Minute);
  y =   tm.Year ;
  m = tm.Month;
  d = tm.Day;
  lon = convertDegMinToDecDeg(givenlongitude);
  lat= convertDegMinToDecDeg(givenlatitude);
  float diff = 5.30;

  //calculation of sunrise and sunset as per data from GPS  
  Dusk2Dawn place(lon, lat, diff);
  int placeSunrise  = place.sunrise(y, m, d, false);
  int placeSunset   = place.sunset(y, m , d, false);
  
  char time1[6];
  Dusk2Dawn::min2str(time1, placeSunrise);
  Serial.println(time1); 

  char time2[6];
  Dusk2Dawn::min2str(time2, placeSunset);
  Serial.println(time2); 

  placeSunrise = r;
  placeSunset = s;


  servo1.attach(4);
  servo1.write(180);
  delay(500);

  }
  
  void loop()
  {
  
  for(i=r; i<=s ; i++)
  {
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH);  
  delay(60000);
  
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, HIGH); 
  delay(10000);
  }
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, LOW);
}
