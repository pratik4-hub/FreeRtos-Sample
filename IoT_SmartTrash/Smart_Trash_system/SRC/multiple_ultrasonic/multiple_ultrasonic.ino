
#define TRIGGER1 5
#define ECHO1 4
#define TRIGGER2 D6
#define ECHO2 D7

long duration, distance, Dustbin1,Dustbin2;

void setup() {
Serial.begin (115200);
pinMode(TRIGGER1, OUTPUT);
pinMode( ECHO1, INPUT);
pinMode(TRIGGER2, OUTPUT);
pinMode(ECHO2, INPUT);
 
}

void loop() {
  Ultrasonic(TRIGGER1,ECHO1);
  Dustbin1=distance;
  Serial.print("Dustbin1:");
  Serial.println(Dustbin1);
  
  delay(2000);

  Ultrasonic(TRIGGER2,ECHO2);
  Dustbin2=distance;
  Serial.print("Dustbin2:");
  Serial.println(Dustbin2);
  delay(2000);
  

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
