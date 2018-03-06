#include "LiquidCrystal.h"
LiquidCrystal lcd(D0,D1,D5,D6,D7,D8);

void setup() {

lcd.begin(16,2);

// set cursor position to start of first line on the LCD
lcd.setCursor(0,0);
//text to print
lcd.print("   16x2 LCD");
// set cusor position to start of next line
lcd.setCursor(0,1);
lcd.print("   DISPLAY");
}
void loop()
{}
