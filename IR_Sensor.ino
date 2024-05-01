void setup() 
{
  Serial.begin(9600);//enable serial monitor
  pinMode(2, INPUT);//define arduino pin
  pinMode(3, OUTPUT);//define arduino pin
  
}

void loop() 
{
  bool value = digitalRead(2);//saves the boolean value
  if(value = 1)
  {
    Serial.println("Card Detected");
    digitalWrite(3,HIGH);//LED on
    
  }
  else
  {
    Serial.println("Card Removed");
    digitalWrite(3,LOW);//LED off
  }

unsigned long time = millis();                         
  const unsigned long tenMinutes = 10 * 60 * 1000;  
  static unsigned long lastSampleTime = 0 - tenMinutes;  
  if (time - lastSampleTime >= tenMinutes){        //If 10 minute is passed, do the desired operations
    lastSampleTime = lastSampleTime + tenMinutes;
    Serial.println("No Card");
    digitalWrite(3,HIGH);//LED on    
}  

}
