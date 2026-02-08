#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ------------------- PIN CONFIG -------------------
#define POT_PIN     34   // Weight via analog
#define PIR_PIN     27   // PIR sensor

// RGB LED pins
#define LED_R 14
#define LED_G 13
#define LED_B 12

// LCD

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);


// ------------------- THRESHOLDS -------------------
int NO_WEIGHT_THRESHOLD = 900;     // ADC<900 → no weight
int RESERVED_THRESHOLD  = 2500;    // between → reserved

// 20 minutes → 20 * 60 * 1000 = 1,200,000 ms
// For testing, change to 20000 (20s)
unsigned long RESERVE_TIMEOUT = 20UL * 60UL * 1000UL;

// ------------------- STATES -------------------
enum SeatState { AVAILABLE, RESERVED, OCCUPIED };
SeatState seatState = AVAILABLE;

unsigned long reserveStartTime = 0;

// --------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("LCD OK!");

  showLCD("Initializing...", "");
  delay(1000);
}

// --------------------------------------------------
void loop() {
  int potValue = analogRead(POT_PIN); // 0–4095
  bool pirValue = digitalRead(PIR_PIN);

  bool hasWeight = (potValue >= NO_WEIGHT_THRESHOLD);
  bool strongWeight = (potValue >= RESERVED_THRESHOLD);

  // ---------------- STATE MACHINE ----------------
  switch (seatState) {

    case AVAILABLE:
      if (hasWeight) {
        if (pirValue) {
          seatState = OCCUPIED;
        } else {
          seatState = RESERVED;
          reserveStartTime = millis();
        }
        updateLEDs();
      }
      break;

    case RESERVED:
      if (!hasWeight) {
        seatState = AVAILABLE;
        updateLEDs();
      }
      else if (hasWeight && pirValue) {
        seatState = OCCUPIED;
        updateLEDs();
      }
      else {
        unsigned long elapsed = millis() - reserveStartTime;
        if (elapsed >= RESERVE_TIMEOUT) {
          seatState = AVAILABLE;
          updateLEDs();
        }
      }
      break;

    case OCCUPIED:
      if (!hasWeight) {
        seatState = AVAILABLE;
        updateLEDs();
      }
      break;
  }

  updateLCD(potValue, pirValue);
  delay(200);
}

// --------------------------------------------------
//       RGB LED CONTROL FOR 3 STATES
// --------------------------------------------------
void updateLEDs() {
  switch (seatState) {
    case AVAILABLE:       // GREEN
      rgb(0, 255, 0);
      break;

    case RESERVED:        // YELLOW = RED + GREEN
      rgb(255, 255, 0);
      break;

    case OCCUPIED:        // RED
      rgb(255, 0, 0);
      break;
  }
}

// RGB LED helper
void rgb(int r, int g, int b) {
  digitalWrite(LED_R, r > 0 ? HIGH : LOW);
  digitalWrite(LED_G, g > 0 ? HIGH : LOW);
  digitalWrite(LED_B, b > 0 ? HIGH : LOW);
}

// --------------------------------------------------
//                 LCD DISPLAY
// --------------------------------------------------
void updateLCD(int weight, int pir) {
  lcd.clear();
  lcd.setCursor(0,0);

  switch (seatState) {
    case AVAILABLE:
      lcd.print("Seat: AVAILABLE");
      break;

    case RESERVED: {
      lcd.print("Seat: RESERVED");

      lcd.setCursor(0,1);
      unsigned long elapsed = millis() - reserveStartTime;
      long remaining = (long)RESERVE_TIMEOUT - (long)elapsed;
      if (remaining < 0) remaining = 0;

      unsigned long secs = remaining / 1000;
      int mins = secs / 60;
      int s = secs % 60;

      char buf[16];
      sprintf(buf, "Time: %02d:%02d", mins, s);
      lcd.print(buf);
      return;
    }

    case OCCUPIED:
      lcd.print("Seat: OCCUPIED");
      break;
  }

  lcd.setCursor(0,1);
  char data[16];
  sprintf(data, "ADC:%4d PIR:%d", weight, pir);
  lcd.print(data);
}

void showLCD(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(l1);
  lcd.setCursor(0,1); lcd.print(l2);
}

