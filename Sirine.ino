#define BUZZER 5  // Pin buzzer (D1 pada ESP8266)

#define BUTTON1 14  // Pin tombol 1 (D5)
#define BUTTON2 12  // Pin tombol 2 (D6)
#define BUTTON3 13  // Pin tombol 3 (D7)
#define BUTTON4 15  // Pin tombol 4 (D8)

void setup() {
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);
}

void loop() {
    if (digitalRead(BUTTON1) == 0 or digitalRead(BUTTON2) == 0 or digitalRead(BUTTON3) == 0 or digitalRead(BUTTON4) == 0) {
    
    if (digitalRead(BUTTON1) == 0) {
      sirine1();
    }
    if (digitalRead(BUTTON2) == 0) {
      sirine2();
    }
    if (digitalRead(BUTTON3) == 0) {
      sirine3();
    }
    if (digitalRead(BUTTON4) == 0) {
      sirine4();
    }
  } else {
    noTone(BUZZER);
  }
}

// Sirine 1: Nada naik turun cepat
void sirine1() {
  for (int i = 500; i <= 2000; i += 20) {
    tone(BUZZER, i);
    delay(5);
  }
  for (int i = 2000; i >= 500; i -= 20) {
    tone(BUZZER, i);
    delay(5);
    }
}

// Sirine 2: Beep Beep dengan delay
void sirine2() {
  tone(BUZZER, 1000);
  delay(300);
  tone(BUZZER, 900);
  delay(300);
}

// Sirine 3: Nada panjang putus-putus
void sirine3() {
  tone(BUZZER, 100);
  delay(50);
  noTone(BUZZER);
  delay(50);
}

// Sirine 4: Sirine polisi (cepat naik turun)
void sirine4() {
  for (int i = 800; i <= 1500; i += 50) {
      tone(BUZZER, i);
      delay(10);
  }
  for (int i = 1500; i >= 800; i -= 50) {
      tone(BUZZER, i);
      delay(10);
  }
}
