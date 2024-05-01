int sensor_value = 0;
int threshold = 540; 
int abs_value = 0;
int ledCount = 10; //number of Bargraph LEDs
int bargraph[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
void setup() {
Serial.begin(9600); 
for (int i = 0; i <= ledCount; i++) 
{
pinMode(bargraph[i], OUTPUT);
}
for (int i = 0; i <= 9; i++)
{
digitalWrite(i, LOW);
}
}
void loop() {
sensor_value = analogRead(A0);
abs_value = abs(sensor_value - threshold);
int ledLevel = map(abs_value, 0, (1024 - threshold), 0, ledCount);
for (int i = 0; i < ledCount; i++) {
if (i < ledLevel) {
digitalWrite(bargraph[i], HIGH);
Serial.println(i);
}
else {
digitalWrite(bargraph[i], LOW); }
 }
 }
