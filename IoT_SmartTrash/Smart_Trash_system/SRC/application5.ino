#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define TRIGGER1 D1
#define ECHO1    D2
#define TRIGGER2 D6
#define ECHO2    D7 

#define RED_LED1  D0
#define RED_LED2  D8
long duration, distance, Dustbin1,Dustbin2;
// credentials
const char *ssid = "HomeLander";
const char *password = "abcdefgh";


void setup() {
   Serial.flush();
  Serial.begin (115200);
  
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(RED_LED1, OUTPUT);
  pinMode(RED_LED2, OUTPUT);
  
   // discover the network
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);

   // wait till you receive a valid IP address
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print("connecting...");
   }

    // now you are connected
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
  //sensor1
  
   // create the client
  HTTPClient httpClient;
  
  Ultrasonic(TRIGGER1,ECHO1);
  Dustbin1=distance;
  Serial.print("Dustbin1:");
  Serial.println(Dustbin1);
  if(Dustbin1<10)
  {
    digitalWrite(RED_LED1,HIGH);
    delay(2000);
    digitalWrite(RED_LED1,LOW);
  }
  
  String body1 = "{ \"dist1\": " + String(Dustbin1) + " }";
  Serial.println("sending :" + body1);
 
  // call the API to insert distance in the MySQL DB
  String url1 = "http://172.18.4.145:5000/dist1";
  
  httpClient.begin(url1);
  httpClient.addHeader("Content-Type", "application/json");
  int code1 = httpClient.POST(body1);
  Serial.println("Status code: " + String(code1));
  // end the connection
  httpClient.end();

  
  delay(5000);
  
 //sensor2
  Ultrasonic(TRIGGER2,ECHO2);
  Dustbin2=distance;
  Serial.print("Dustbin2:");
  Serial.println(Dustbin2);

  if(Dustbin2<10)
  {
    digitalWrite(RED_LED1,HIGH);
    delay(2000);
    digitalWrite(RED_LED1,LOW);
  }
     
  String body2 = "{ \"dist2\": " + String(Dustbin2) + " }";
  Serial.println("sending :" + body2);
  
  // call the API to insert distance in the MySQL DB
  String url2= "http://172.18.4.145:5000/dist2";
  
  httpClient.begin(url2);
  httpClient.addHeader("Content-Type", "application/json");
  int code2= httpClient.POST(body2);

  Serial.println("Status code: " + String(code1));
  // end the connection
  httpClient.end();

  
}
void Ultrasonic(int TRIGGER,int ECHO)
{
digitalWrite(TRIGGER, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER, LOW);
duration = pulseIn(ECHO, HIGH);
distance = (duration/2) / 29.1;
}
