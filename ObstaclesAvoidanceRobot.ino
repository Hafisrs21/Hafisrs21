#include <NewPing.h>     // konfigurasi sensor hcsr04

#define TRIGGER_PIN1  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     15  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  16  
#define ECHO_PIN2     4
#define TRIGGER_PIN3  5  
#define ECHO_PIN3     17
#define TRIGGER_PIN4  19  
#define ECHO_PIN4     18
#define TRIGGER_PIN5  23  
#define ECHO_PIN5     22
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int distanceKiri = 100;
int distanceTengahKiri = 100;
int distanceTengah = 100;
int distanceTengahKanan = 100;
int distanceKanan = 100;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE);
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE);

int kirimaju = 33;          //konfigurasi pin output motor
int kananmaju = 26;
int kirimundur = 25;
int kananmundur = 27;

const int enb = 14;         //set analogWrite
const int ena = 32;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int dutyCycle = 170;

unsigned long startTime;    //set timer

void setup() {
  Serial.begin(115200);
  
  pinMode(kirimaju, OUTPUT);
  pinMode(kananmaju, OUTPUT);
  pinMode(kirimundur, OUTPUT);
  pinMode(kananmundur, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ena, ledChannel);
  ledcAttachPin(enb, ledChannel);

  startTime = millis();  // Set the start time
}

void loop() {
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("sensorkiri: ");
  Serial.print(sonar1.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm");
  Serial.print("sensortengahkiri: ");
  Serial.print(sonar2.ping_cm());
  Serial.print("cm");
  Serial.print("sensortengah: ");
  Serial.print(sonar3.ping_cm());
  Serial.print("cm");
  Serial.print("sensortengahkanan: ");
  Serial.print(sonar4.ping_cm());
  Serial.print("cm");
  Serial.print("sensorkanan: ");
  Serial.print(sonar5.ping_cm());
  Serial.print("cm");
  Serial.println(" ");

  distanceKiri = readPingKiri(); // update distance
  distanceTengahKiri = readPingTengahKiri();
  distanceTengah = readPingTengah();
  distanceTengahKanan = readPingTengahKanan();
  distanceKanan = readPingKanan();

  // Calculate the progressive distance threshold
  unsigned long elapsedTime = millis() - startTime;
  int distanceThreshold;

  if (elapsedTime < 1500) {
    distanceThreshold = 10 + (15 * elapsedTime) / 1500; // Increase linearly from 10 cm to 25 cm over 1.5 seconds
  } else {
    distanceThreshold = 20; // After 1.5 seconds, the threshold stays at 25 cm
  }

  if (distanceTengah <= distanceThreshold){
    mundur();
  }
  else if(distanceTengahKanan <= distanceThreshold){
    belokKiri();
  }
  else if(distanceKanan <= distanceThreshold){
    putarKiri();
  }
  else if(distanceTengahKiri <= distanceThreshold){
    belokKanan();
  }
  else if(distanceKiri <= distanceThreshold){
    putarKanan();
  }
  else{
    maju();
  }
}

int readPingKiri(){
  delay(70);
  int cm = sonar1.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

int readPingTengahKiri(){
  delay(70);
  int cm = sonar2.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

int readPingTengah(){
  delay(70);
  int cm = sonar3.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

int readPingTengahKanan(){
  delay(70);
  int cm = sonar4.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

int readPingKanan(){
  delay(70);
  int cm = sonar5.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void maju(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, HIGH);
  digitalWrite(kananmaju, HIGH);

  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmundur, LOW);
  }

void mundur(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, LOW);
  digitalWrite(kananmaju, LOW);

  digitalWrite(kirimundur, HIGH);
  digitalWrite(kananmundur, HIGH);
}

void belokKiri(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, LOW);
  digitalWrite(kananmaju, HIGH);

  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmundur, LOW);
}

void putarKiri(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, LOW);
  digitalWrite(kananmaju, HIGH);

  digitalWrite(kirimundur, HIGH);
  digitalWrite(kananmundur, LOW);
}

void belokKanan(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, HIGH);
  digitalWrite(kananmaju, LOW);

  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmundur, LOW);
}

void putarKanan(){
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(kirimaju, HIGH);
  digitalWrite(kananmaju, LOW);

  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmundur, HIGH);
}

void berhenti(){
  digitalWrite(kirimaju, LOW);
  digitalWrite(kananmaju, LOW);

  digitalWrite(kirimundur, LOW);
  digitalWrite(kananmundur, LOW);
}