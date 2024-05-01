#include <DFRobot_ID809.h>

#define COLLECT_NUMBER 1  //To set one fingerprint sample
#define IRQ         6  //IRQ pin 
#define FPSerial Serial1

#include <SoftwareSerial.h>//import fingerprint library for Arduino
SoftwareSerial Serial1(2, 3);  //set software serial on pins 2 and 3,pin 2 as RX and pin 3 as TX

DFRobot_ID809 fingerprint;
//String desc;
void fingerprintMatching();
void fingerprintRegistration();
void setup(){
  
  Serial.begin(9600);//fingerprint sensor module setup
  FPSerial.begin(115200);//init FPSerial
  fingerprint.begin(FPSerial);//Take FPSerial as communication serial of fingerprint module
  
  while(!Serial);// wait for serial to open

  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    delay(1000);
  }
}

void loop(){
  if(digitalRead(IRQ)){
    uint16_t i = 0;//
    /*Capture fingerprint image, 5s idle timeout, if timeout=0,Disable  the collection timeout function
      Return 0 if succeed, otherwise return ERR_ID809
     */
    if((fingerprint.collectionFingerprint(/*timeout=*/5)) != ERR_ID809){
     
      while(fingerprint.detectFinger()){
        //detects fingerprint after finger is pressed down
        delay(50);
        i++;
        }
    }
    
    if(i == 0){
      Serial.println("INVALID");//fingerprint capture failes=d
    }
    else if(i > 0 && i < 15)
    {
      fingerprintMatching();//compare fingerprint
    }
    else
      fingerprintRegistration();//register fingrprint  
  }
}

//Fingerprint Registration of the User
void fingerprintRegistration(){
  uint8_t ID,i;  //compares the user's fingerprint
  fingerprint.search();   //Can add "if else" statement to judge whether the fingerprint has been registered. 
  //if no fingerprint in the library the add fingerprint
  if((ID = fingerprint.getEmptyID()) == ERR_ID809){
    while(1){
      /*Get error code imformation*/
      delay(1000);
    }
  }
  Serial.print("Unregistered ID,ID=");
  Serial.println(ID);
  i = 0;   //Clear sampling times 
  
  while(i=1){
    Serial.println("Please press down your finger");
    
    if((fingerprint.collectionFingerprint(/*timeout = */10)) != ERR_ID809){
    //if sucessful return to zero else show error
    //10 second timeout to capture fingerprint
      Serial.println("Capturing succeeds");
      i++;   //Sampling times +1 
    }else{
      Serial.println("Capturing fails");
    }
    Serial.println("Please release your finger");
   //Return 1 when finger is detected, otherwise return 0 
     while(fingerprint.detectFinger());
  }

  //Save fingerprint information into an unregistered ID
  if(fingerprint.storeFingerprint(/*Empty ID = */ID) != ERR_ID809){
    Serial.print("Saving succeed，ID=");
    Serial.println(ID);
    }else{
    Serial.println("Saving failed");
    //Get error code information  
  }
}

//Compare fingerprints with fingerprint stored in the library
void fingerprintMatching()
{
  uint8_t ret = fingerprint.search();
  if(ret != 0)
  {
    Serial.print("Successfully matched,ID=");
    Serial.println(ret);
  }
  else
  {
    Serial.println("Matching failed");
  }
  delay(1000); 
}
