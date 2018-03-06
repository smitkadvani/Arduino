/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

*/
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
  Serial.begin(9600);
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Heart Rate Value:");
  pinMode(ledPin, OUTPUT);
  mySerial.begin(115200);
  
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
  lcd.print(sensorValue);
  mySerial.println(""+sensorValue);
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

