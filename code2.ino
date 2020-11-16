//Sun Position Calculation

#include <math.h>
#define pi    3.14159265358979323846
#define twopi (2*pi)
#define rad   (pi/180)
#define EarthMeanRadius     6371.01      // In km
#define AstronomicalUnit    149597890      // In km

//Input Variables TIME IN UST ONLY
    int Year = 2019; //year
    int Month = 5; //month
    int Day = 21; //day
    float Hours = 10; //hour
    float Minutes = 30; //minutes

    float Longitude = 72.8777; //enter longitude here
    float Latitude = 19.0760; //enter latitude here
//

//Program Variables
    float ZenithAngle;
    float Azimuth;
      float RightAscension;
    float Declination;
      float Parallax;
      float ElevationAngle;

    float ElapsedJulianDays;
    float DecimalHours;
    float EclipticLongitude;
    float EclipticObliquity;
//

void setup() {
Serial.begin(9600);
}

void sunPos(){


    // Auxiliary variables
    float dY;
    float dX;

    // Calculate difference in days between the current Julian Day
    // and JD 2451545.0, which is noon 1 January 2000 Universal Time

          float JulianDate;
          long int liAux1;
          long int liAux2;
          // Calculate time of the day in UT decimal hours
          DecimalHours = Hours + (Minutes / 60.0);
          // Calculate current Julian Day
          liAux1 =(Month-14)/12;
          liAux2=(1461*(Year + 4800 + liAux1))/4 + (367*(Month
                - 2-12*liAux1))/12- (3*((Year + 4900
          + liAux1)/100))/4+Day-32075;
          JulianDate=(float)(liAux2)-0.5+DecimalHours/24.0;
          // Calculate difference between current Julian Day and JD 2451545.0
          ElapsedJulianDays = JulianDate-2451545.0;

    // Calculate ecliptic coordinates (ecliptic longitude and obliquity of the
    // ecliptic in radians but without limiting the angle to be less than 2*Pi
    // (i.e., the result may be greater than 2*Pi)

          float MeanLongitude;
          float MeanAnomaly;
          float Omega;
          Omega=2.1429-0.0010394594*ElapsedJulianDays;
          MeanLongitude = 4.8950630+ 0.017202791698*ElapsedJulianDays; // Radians
          MeanAnomaly = 6.2400600+ 0.0172019699*ElapsedJulianDays;
          EclipticLongitude = MeanLongitude + 0.03341607*sin( MeanAnomaly )
                + 0.00034894*sin( 2*MeanAnomaly )-0.0001134
                -0.0000203*sin(Omega);
          EclipticObliquity = 0.4090928 - 6.2140e-9*ElapsedJulianDays
                +0.0000396*cos(Omega);

    // Calculate celestial coordinates ( right ascension and declination ) in radians
    // but without limiting the angle to be less than 2*Pi (i.e., the result may be
    // greater than 2*Pi)

          float Sin_EclipticLongitude;
          Sin_EclipticLongitude= sin( EclipticLongitude );
          dY = cos( EclipticObliquity ) * Sin_EclipticLongitude;
          dX = cos( EclipticLongitude );
          RightAscension = atan2( dY,dX );
          if( RightAscension < 0.0 ) RightAscension = RightAscension + twopi;
          Declination = asin( sin( EclipticObliquity )*Sin_EclipticLongitude );

    // Calculate local coordinates ( azimuth and zenith angle ) in degrees

          float GreenwichMeanSiderealTime;
          float LocalMeanSiderealTime;
          float LatitudeInRadians;
          float HourAngle;
          float Cos_Latitude;
          float Sin_Latitude;
          float Cos_HourAngle;
          GreenwichMeanSiderealTime = 6.6974243242 +
                0.0657098283*ElapsedJulianDays
                + DecimalHours;
          LocalMeanSiderealTime = (GreenwichMeanSiderealTime*15
                + Longitude)*rad;
          HourAngle = LocalMeanSiderealTime - RightAscension;
          LatitudeInRadians = Latitude*rad;
          Cos_Latitude = cos( LatitudeInRadians );
          Sin_Latitude = sin( LatitudeInRadians );
          Cos_HourAngle= cos( HourAngle );
          ZenithAngle = (acos( Cos_Latitude*Cos_HourAngle
                *cos(Declination) + sin( Declination )*Sin_Latitude));
          dY = -sin( HourAngle );
          dX = tan( Declination )*Cos_Latitude - Sin_Latitude*Cos_HourAngle;
          Azimuth = atan2( dY, dX );
          if ( Azimuth < 0.0 )
            Azimuth = Azimuth + twopi;
          Azimuth = Azimuth/rad;
          
// Parallax Correction
          Parallax=(EarthMeanRadius/AstronomicalUnit)
                *sin(ZenithAngle);
          ZenithAngle=(ZenithAngle //Zenith angle is from the top of the visible sky (
                + Parallax)/rad;
              ElevationAngle = (90-ZenithAngle); //Retrieve useful elevation angle from Zenith angle
}

void loop(){
sunPos(); //Run sun position calculations
Serial.print("Elevation Angle:  ");
Serial.println(ElevationAngle, 0); //Print Elevation (Vertical) with no decimal places 
Serial.print("Azimuth:  ");
Serial.println(Azimuth, 0); //Print Azimuth (Horizontal) with no decimal places
if(ElevationAngle < 0)
//code to stop the motors of the tracker 
while(1){} //Stop 
}

