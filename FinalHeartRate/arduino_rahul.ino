#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0,sens;  // variable to store the value coming from the sensor
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int analogue=0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Heart Rate Value:");
  pinMode(ledPin, OUTPUT);
 // mySerial.begin(115200);
  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  lcd.setCursor(0,0);
  lcd.print("Heart Rate Value:");
  lcd.setCursor(0,1);
  HeartRate();
  sensorValue/=10;
  sensorValue = (sensorValue/100)*8  + (sensorValue%100);
  lcd.print(sensorValue);
  //mySerial.println(""+sensorValue);
  Serial.println(sensorValue);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}

int HeartRate()
{
   while(sensorValue<=720)
   {
      sens = analogRead(sensorPin);
      sensorValue = sens;
      delay(50);

   }
   if(sens <=700)
   {
      //No Change
   }
   
   
   if(sensorValue>=1000)
   {
   delay(500);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Heart Rate Value:");
   while(sensorValue >=1000)
   {
       sensorValue = analogRead(sensorPin);
      lcd.setCursor(0,1);
      lcd.print("Sensor out of Service");
      delay(100);
   }
   delay(500);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Heart Rate Value:");
   }
}
