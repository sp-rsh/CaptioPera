// TCS230 or TCS3200 pins wiring to Arduino Nano
#define s0 4
#define s1 5
#define s2 6
#define s3 7
#define outPin 8


//Define Variables
int red;
int grn;
int blu;
int count = 0;


void setup() 
{
   pinMode(s0,OUTPUT);    
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(outPin,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void loop()
{
  getColor() ;                                   //Execute the getColor function

}

void getColor()
{  
  readRGB();
  
  if (red > 8 && red < 18 && grn > 9 && grn < 19 && blu > 8 && blu < 16) //for color = "WHITE" 
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
    
  
  else if (red > 80 && red < 125 && grn > 90 && grn < 125 && blu > 80 && blu < 125) //for color = "BLACK";
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
  
  else if (red > 12 && red < 30 && grn > 40 && grn < 70 && blu > 33 && blu < 70)//for color = "RED";
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
  
  else if (red > 50 && red < 95 && grn > 35 && grn < 70 && blu > 45 && blu < 85) //for color = "GREEN";
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
  
  else if (red > 10 && red < 20 && grn > 10 && grn < 25 && blu > 20 && blu < 38) //for color = "YELLOW";
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
  
  else if (red > 65 && red < 125 && grn > 65 && grn < 115 && blu > 32 && blu < 65) //for color = "BLUE";
    {serial.print("Red value= ");
     serial.print("Green value= ");
     serial.print("Blue value= ");
    }
  else 
    {color = "NO_COLOR";}
}

/* read RGB components */
void readRGB() 
{
  red = 0;
  grn = 0;
  blu = 0;
  int n = 10;
  for (int i = 0; i < n; ++i)
  {
    //read red component
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
    // GetData();
  
   //read green component
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    /*GetData();*/
    
   //let's read blue component
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
    // GetData();
  }
  red = red/n;
  grn = grn/n;
  blu = blu/n;
}
