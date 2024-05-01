#include <SoftwareSerial.h>

#define LED 13

// software SIM808 #:  RX = digital pin 2,TX = digital pin 3
SoftwareSerial SIM808(2, 3);

String msg = "";
bool answer;
char frame[200];
char latitude[15];
char longitude[15];
char altitude[6];

// SETUP CODE
void setup() {
  SIM808.begin(9600);  
  pinMode(LED, OUTPUT);
  Serial.println("Sending Location...");
  GSM_Connect(); // GSM CONNECT
  GPS_connect();
  digitalWrite(LED, LOW);
}

// LOOPING CODE
void loop() {
  if (SIM808.available() > 0)
  {
    send_sms();
  }
  delay(1);
}

// FUNCTIONS
void GSM_Connect() {
  Serial.println("GSM Connecting ...");
  // checks if the module is started
  answer = 0;
  digitalWrite(LED, LOW);
  while (answer == 0) {
    if (answer == 0) {
      Serial.println("No Connection...");
    }
  }
  digitalWrite(LED, HIGH);
  Serial.println("Ok.");
  answer = 0;
}

// ACTIVATING GPS

int8_t GPS_connect() {

  Serial.println("Starting GPS...");
  unsigned long previous;
  previous = millis();
  // starts the GPS
  Serial.print(".");

  // waits for fix GPS
  answer = 0;
  while ((answer == 0) && (millis() - previous < 60000)) {
    Serial.print(".");
  }
  //Serial.println("Finish");
  return answer;
}

// READ SMS
void read_sms() {
  msg = "";
  Serial.println("Reading SMS...");
  Serial.println("Message : ");
  while ( SIM808.available()) {
    char SIM808InByte = SIM808.read();
    msg += SIM808InByte;
    Serial.print(SIM808InByte);
    delay(3);
  }

  if (msg.indexOf("Get pos") >= 0) {
    get_GPS();  
    send_sms();
  }
  delay(100);
  while ( SIM808.available()) {
    SIM808.read();
    delay(4);
  }
  Serial.println("Read done ********");
  SIM808.flush();
}

// GETTING THE GPS LOCATION
int8_t get_GPS() {
  Serial.println("\nGeting GPS Location");
  int8_t counter;
  long previous;
  // First get the NMEA string
  // Clean the input buffer
  // request Basic string
 // sendATcommand("AT+CGNSINF", "+CGNSINF:", 2000);

  counter = 0;
  answer = 0;
  memset(frame, '\0', 100);    // Initialize the string
  previous = millis();
  // this loop waits for the NMEA string
  do {
    if (SIM808.available() != 0) {
      frame[counter++] = SIM808.read();
      // check if the desired answer is in the response of the module
      if (strstr(frame, "OK") != NULL)
      {
        answer = 1;
      }
      delay(5);
    }
    // Waits for the answer with time out
  }
  while ((answer == 0) && ((millis() - previous) < 3000));
  while ( SIM808.available() > 0) SIM808.read();
  Serial.println("--------------------------------------");
  Serial.println(frame);
  Serial.println("*****");
  frame[counter - 3] = '\0';

  // Parses the string
  //We will now use strtok() to break up our string into it's discrete tokens.

  strtok(frame, ",");
  strtok(NULL, ",");
  strtok(NULL, ",");
  strcpy(longitude, strtok(NULL, ",")); // Gets longitude
  strcpy(latitude, strtok(NULL, ",")); // Gets latitude
  strcpy(altitude, strtok(NULL, ".")); // Gets altitude

  Serial.print("latitude:");
  Serial.println(latitude);
  Serial.print("longitude:");
  Serial.println(longitude);
  Serial.print("altitude:");
  Serial.println(altitude);

  Serial.print("http://maps.google.com/?q=");
  Serial.print(longitude);
  Serial.print(',');
  Serial.println(latitude);
  return answer;
}

// SENDING SMS
void send_sms() {
  SIM808.println("AT+CMGF=1");// SMS Mode
  delay(1000);
  SIM808.println("AT+CMGS=\"9811363737\"");//Receiver phone number
  delay(1000);
  SIM808.print("http://maps.google.com/?q=");
  SIM808.print("Longitude: ");
  SIM808.print(longitude);
  SIM808.print(',');
  SIM808.println("Latitude: ");
  SIM808.println(latitude);
  delay(1000);
  SIM808.write(26);// end sms
  Serial.println("Location Sent");
  delay(1000);

}
