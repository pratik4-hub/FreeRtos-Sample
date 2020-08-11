#include <Wire.h>
#include <dht.h>  // addition of dth11(Humidity and Temperature Sensor) Library!!!
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

double alpha = 0.75;
static double oldValue = 0;
int period = 20;
double refresh = 0.0;

String apiKey = "3A2R29RC1IARUSRP";     //Key from ThingSpeak(Channel Id)
const char *ssid =  "INDRA";
const char *pass =  "33335555";
const char* server_ = "api.thingspeak.com";
dht11 DHT; // Creats a DHT object
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


#define DHTPIN 0       //dht11 connection pin
WiFiClient client;
/////////////////////////////////////////////////////////////////////////////////

void root() {
  server.send(200, "text/plain", "Welcome to IoAHT web server");
}


void get_current_temperature() {
  float temp = DHT.temperature;
  String result = "Current Temperature = " + String(temp);
  server.send(200, "text/plain", result);
}

void get_current_humidity() {
  float humidity = DHT.humidity;
  String result = "Current Humidity = " + String(humidity);
  server.send(200, "text/plain", result);
}

void get_current_pressure() {
  sensors_event_t event;
  bmp.getEvent(&event);
  long up = event.pressure;
  String result = "Current Pressure = " + String(up);
  server.send(200, "text/plain", result);
}

/*void get_current_pulses() {
  float temp = analogRead(A0);
  String result = "Current Temperature = " + String(temp);
  server.send(200, "text/plain", result);
  }*/

void get_current_gases() {
  float gas = digitalRead(D8);
  String result = "Current Gas_Reading = " + String(gas / 10);
  server.send(200, "text/plain", result);
}

void setup()
{
  Serial.begin(115200);
  Serial.flush();
  pinMode(D8, INPUT);
  delay(10);
  pinMode(A0, INPUT);
  delay(10);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    delay(1);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  if (!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  server.on("/", HTTP_GET, root);
  server.on("/temp", HTTP_POST, get_current_temperature);
  server.on("/humidity", HTTP_GET, get_current_humidity);
  server.on("/pressure", HTTP_GET, get_current_pressure);
  // server.on("/pulse", HTTP_GET, get_current_pulses);
  server.on("/gas", HTTP_GET, get_current_gases);

  server.begin();

}

void loop()
{
  server.handleClient();
  delay(1000);
  int readData = DHT.read(DHTPIN); // Reads the data from the sensor
  float temp = DHT.temperature; // Gets the values of the temperature
  float hum = DHT.humidity;
  float gas = digitalRead(D8);
  
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
  }

  delay(5000);
  int beats;
  int beat = analogRead(A0);
  double pulse = alpha * oldValue + (0 - alpha) * beat;
  refresh = pulse - oldValue;
  Serial.print(" value:  ");
  Serial.println(beat / 7);
  beats = beat / 7;
  oldValue = pulse;
  double oldrefresh = refresh;
  delay(period * 7);
  if (client.connect(server_, 80))  //api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temp);
    postStr += "&field2=";
    postStr += String(hum);
    postStr += "&field3=";
    postStr += String(event.pressure);
    postStr += "&field4=";
    postStr += String(beats);
    postStr += "&field5=";
    postStr += String(gas);
    //postStr += "&field6=";
    //postStr += String(gas / 10);
    postStr += "\r\n\r\n";


    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println();
    Serial.print("Compensated pressure P = ");
    Serial.print(event.pressure);
    Serial.print(" (");
    Serial.println(event.pressure);
    Serial.print(" hPa)");
    Serial.println();
    Serial.println("Temperature: ");
    Serial.print(temp);
    Serial.println();
    Serial.println(" degrees Celcius, Humidity: ");
    Serial.print(hum);
    Serial.print("%");
    Serial.println();
    Serial.println("Heart Pulses: ");
    Serial.print(beats);
    Serial.println();
    Serial.println("Gas reading: ");
    Serial.print(gas);
    Serial.println();
    if(gas==1)
    {
        Serial.println("harmful gases detected, please be careful");
    }
    
    Serial.println("Data Sent to Thingspeak.");
  }
  client.stop();
  /******************DONE WITH THINGSPEAK***************************************/
  HTTPClient httpClient;
  String body1 = "{ \"humidity\": " + String(hum) + "}";
  Serial.println("sending :" + body1);
  String url1 = "http://192.168.43.89:5000/humidity";

  httpClient.begin(url1);
  httpClient.addHeader("Content-Type", "application/json");
  int code1 = httpClient.POST(body1);

  Serial.println("Status code: " + String(code1));
  httpClient.end();

  Serial.println("Waiting...");

  /**********************************temp****************************************/
  String body2 = "{ \"temp\": " + String(temp) + "}";
  Serial.println("sending :" + body2);
  String url2 = "http://192.168.43.89:5000/temp";

  httpClient.begin(url2);
  httpClient.addHeader("Content-Type", "application/json");
  int code2 = httpClient.POST(body2);

  Serial.println("Status code: " + String(code2));
  httpClient.end();


  Serial.println("Waiting...");
  /**************************pressure********************************************/


  String body3 = "{ \"pressure\": " + String(event.pressure) + "}";
  Serial.println("sending :" + body3);
  String url3 = "http://192.168.43.89:5000/pressure";

  httpClient.begin(url3);
  httpClient.addHeader("Content-Type", "application/json");
  int code3 = httpClient.POST(body3);

  Serial.println("Status code: " + String(code3));
  httpClient.end();


  Serial.println("Waiting...");


  /****************************************Pulses*************************************/
  String body4 = "{ \"hp\": " + String(beats) + "}";
  Serial.println("sending :" + body4);
  String url4 = "http://192.168.43.89:5000/hp";

  httpClient.begin(url4);
  httpClient.addHeader("Content-Type", "application/json");
  int code4 = httpClient.POST(body4);

  Serial.println("Status code: " + String(code4));
  httpClient.end();
  delay(2000);


  Serial.println("Waiting...");
  delay(1000);
  /***************************************Gases**************************************/
  String body5 = "{ \"gases\": " + String(gas) + "}";
  Serial.println("sending :" + body5);

  String url5 = "http://192.168.43.89:5000/gases";

  httpClient.begin(url5);
  httpClient.addHeader("Content-Type", "application/json");
  int code5 = httpClient.POST(body5);

  Serial.println("Status code: " + String(code5));

  httpClient.end();


  Serial.println("Waiting...");
}
