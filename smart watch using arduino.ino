#include <LiquidCrystal.h>
#include <Wire.h>  
const int MPU=0x68;
int16_t AcX,AcY,AcZ;    

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
   double a=0.75;
   double r=0.0;
const int inPin = 0; // Analog input for Temperature
void setup(void)
{
  Wire.begin();
  Wire.beginTransmission(MPU); // begin transmission of MPU6050
  Wire.write(0x6B);
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(A1,INPUT);  // Analog input for heartbeat
  lcd.begin(16,2);
}
void loop(void)
{
  // Code for Accelerometer
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read();
  AcY=Wire.read();
  AcZ=Wire.read();
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Accelerometer:");
  lcd.setCursor(0,1);
  lcd.print("X="); lcd.print(AcX);
  lcd.print("|Y="); lcd.print(AcY);
  lcd.print("|Z="); lcd.print(AcZ);
  delay(2500);
  // Code for Heartbeat
  static double oV=0;
  static double oR=0;
  int beat=analogRead(A1);
  double heartvalue=a*oV+(0-a)*beat;
  r=heartvalue-oV;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heartbeat Rate/m");
  lcd.setCursor(0,1);
  lcd.print("          ");
  lcd.setCursor(0,1);
  lcd.print(beat/10);
  oV=heartvalue;
  oR=r;
  delay(2500);
  // Code for Temperature
  int value = analogRead(inPin);
  lcd.setCursor(0,1);
  float mv = (value/1024.0)*3300;
  float c = mv/10;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Body Temperature");
  lcd.setCursor(0,1);
  lcd.print((c*9)/5+ 32);
  lcd.print("F");
  delay(2500);
}