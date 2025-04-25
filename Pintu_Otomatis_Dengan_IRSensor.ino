#include <Servo.h>

#define irSensorPin 5 // Pin D1 input dari ir sensor
#define servoPin 14 // Pin D5 output ke servo

Servo pintuServo;

void setup() {
  pinMode(irSensorPin, INPUT);
  pintuServo.attach(servoPin);
  pintuServo.write(0);
  Serial.begin(115200);
}

void loop() {
  int statusSensor = digitalRead(irSensorPin);

  if (statusSensor == HIGH){
    Serial.println("Objek terdeteksi, membuka pintu....");
    pintuServo.write(90); //buka pintu
  } else {
    Serial.println("Tidak ada objek, menutup pintu");
    pintuServo.write(0); // tutup pintu
  }

  delay (300);
}
