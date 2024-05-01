#include <NeoSWSerial.h>//NeoSWSerial Library
#include <TinyGPS++.h>//TinyGPS++ Library
NeoSWSerial gpsSerial( 2, 3 );//2 and 3 serial communication pins (Rx-Tx)
TinyGPSPlus gps;// defining gps obj
float Latitude;//Latitude Area
float Longitude;//Longitude Area

void setup()
{
  Serial.begin( 9600 );//Arduino Communication Speed (9600 baud)
  gpsSerial.begin( 9600 );//Gps module with Arduino Communication Speed
  delay(2000);//2 seconds delay
}

void loop()
{
 /* if (gpsSerial.available())
    Serial.write( gpsSerial.read() );*/
  while(1)
  {
   while (gpsSerial.available() > 0)//GPS data?
   { 
      gps.encode(gpsSerial.read());//Get data from gps module.
   }

      if (gps.location.isUpdated())//GPS location changed?
      {
       Serial.print("Latitude="); 
       Serial.println(gps.location.lat(), 6);//gps.location.lat() function is used for latitude value. (Print)
       Serial.print("Longitude="); 
       Serial.println(gps.location.lng(), 6);//gps.location.lng() function is used for longitude value. (Print)
       
       Latitude = gps.location.lat();//gps update.
       Longitude = gps.location.lng();//gps update.
       break;
      }
  }
 Serial.print("Latitude ");//Print Latitude value
 delay(500);//delaying 0.5 sec
 Serial.print("Longitude ");
 delay(1000);
}
