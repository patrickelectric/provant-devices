#define MINI
//#define DEBUG


#ifdef NANO
  #define trigPin 2
  #define echoPin 3
  #define led 13
  #define GND 10
#endif
#ifdef MINI
  #define trigPin 17
  //#define trigPin A3
  #define echoPin 16
  //#define echoPin A2
  #define led 13
  #define GND 15
#endif

long duration, distance;
unsigned long atual_time,last_time;

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);  // Added this line
  atual_time = last_time = millis();
}

void loop()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //duration = pulseIn(echoPin, HIGH,11000); //3.4m timeout
  duration = pulseIn(echoPin, HIGH,18000); //3.4m timeout
  distance = (duration/2) / 29.1;

  #if 1
  if (distance < 2) 
    distance=2;
  else
    if(distance > 200) 
      distance = 200;
  #endif
  
  if(distance==2 || distance ==200)
    digitalWrite(led,HIGH);
  else 
    digitalWrite(led,LOW);
  
  while(atual_time-last_time<15)
    atual_time=millis();
    
  
    Serial.print("R");    
    Serial.print((char)distance);
    #ifdef DEBUG
    Serial.print(",");
    Serial.print(distance); //debug

    Serial.print(",");
    Serial.print(duration);

    Serial.print(",");
    Serial.print(atual_time-last_time);

    Serial.println();
    #endif

    last_time=atual_time;
  
}
