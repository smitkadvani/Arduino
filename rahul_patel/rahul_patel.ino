#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup()
{

  

}


void loop()
{

    
    WiFi.softAP("4:20","nahipata");
    while ((!(WiFi.status() == WL_CONNECTED)))
    Serial.print(".");
    delay(300);
    if (client.connect("api.thingspeak.com",80)) {
      writeAPIKey = "key=JYLKR4WVJ5NPEPOC";
      tsfield1Name = "&field1=10";
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "UJHIB0DPYKT771ZX";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += 45;
      //request_string += (analogRead(A0)/10);
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(50);

}
