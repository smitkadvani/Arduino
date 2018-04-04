#include <ESP8266WiFi.h>


#include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;
HTTPClient http;


const char* ssid     = "Smit";
const char* password = "12345678";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";
int calHeartBeat();
int caliBration();
String s = "00";
char c;
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

 // Serial.println();
 // Serial.println();
 // Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   // Serial.print(".");
  }

  //Serial.println("");
  //Serial.println("WiFi connected");  
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  //Serial.print("connecting to ");
  //Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    //Serial.println("connection failed");
    return;
  }
  if (client.connect("api.thingspeak.com",80)) {
      //Serial.println("Contacting ThingSpeak...");
      writeAPIKey = "key=FY52UTY60ED4I2AS";
      tsfield1Name = "&field1=10";
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "FY52UTY60ED4I2AS";
      //request_string += "LCGO8KXLOSZFADZH";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      s = "00";
      if(Serial.available()>0){
          c = (char)Serial.read();
          s.setCharAt(0,c);
          c = (char)Serial.read();
          s.setCharAt(1,c);
          Serial.println(s);
      }
      request_string += s;
      //request_string += (analogRead(A0)/10);
      int i =  http.begin(request_string);
      //Serial.println(analogRead(A0)/10);
      http.GET();
      http.end();

    }
  
}
void functionCall(){
  
  // We now create a URI for the request
  String url = "/input/";
  url += streamId;
  url += "?private_key=";
  url += privateKey;
  url += "&value=";
  url += value;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
int calHeartBeat()
{
  int n;
  n = analogRead(A0)/10;
  if(n<=60)
  {
     //Serial.print("...");
  }
  else 
  {
     n = n-20;
  }
}

int caliBration()
{
  String url;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return 0;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
