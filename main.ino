#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <EEPROM.h>

// Initialize Objects
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

// --- PIN DEFINITIONS ---
#define PIN_COUNT_SW   33 // #14 Assembly Counter
#define PIN_DOOR_BTN   13 // #11 Door Trigger
#define PIN_SERVO      12 // #11 Door Motor
#define PIN_ULTRA_TRIG 14 // #12 Forklift Safety
#define PIN_ULTRA_ECHO 27 // #12 Forklift Safety
#define PIN_BUZZER     26 // #12 Alarm
#define PIN_VEND_BTN   4  // #13 Vending Button
#define PIN_RELAY      25 // #13 Vending Dispenser
#define PIN_PIR        32 // #15 Parking Sensor

// --- GLOBAL VARIABLES ---
int partCount = 0;
bool lastCountState = LOW;
int vendingStock;
const int EEPROM_SIZE = 1;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  EEPROM.begin(EEPROM_SIZE);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize Servo
  doorServo.attach(PIN_SERVO);
  doorServo.write(0);
  
  // Load Inventory from EEPROM (Task #13)
  vendingStock = EEPROM.read(0);
  if (vendingStock > 100) vendingStock = 10; // Reset if memory is empty

  // Pin Configuration
  pinMode(PIN_COUNT_SW, INPUT_PULLUP);
  pinMode(PIN_DOOR_BTN, INPUT_PULLUP);
  pinMode(PIN_VEND_BTN, INPUT_PULLUP);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_ULTRA_TRIG, OUTPUT);
  pinMode(PIN_ULTRA_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("SMART FACTORY");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM ONLINE");
  delay(2000);
  lcd.clear();
}

void loop() {
  handleCounter();   // Zone 1
  handleDoor();      // Zone 2
  handleSafety();    // Zone 3
  handleVending();   // Zone 4
  handleParking();   // Zone 5
  
  delay(50); // General system stability
}

// 1. ASSEMBLY COUNTER (#14)
void handleCounter() {
  bool state = (digitalRead(PIN_COUNT_SW) == LOW);
  if (state && !lastCountState) {
    partCount++;
    Serial.print("PRODUCTION: New Part Count: "); Serial.println(partCount);
    updateLCD();
  }
  lastCountState = state;
}

// 2. SMART DOOR (#11)
void handleDoor() {
  if (digitalRead(PIN_DOOR_BTN) == LOW) {
    doorServo.write(90);
    lcd.setCursor(0, 0); lcd.print("DR:OPEN ");
  } else {
    doorServo.write(0);
    lcd.setCursor(0, 0); lcd.print("DR:SAFE ");
  }
}

// 3. FORKLIFT SAFETY (#12)
void handleSafety() {
  digitalWrite(PIN_ULTRA_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_ULTRA_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_ULTRA_TRIG, LOW);
  
  long duration = pulseIn(PIN_ULTRA_ECHO, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 200) {
    digitalWrite(PIN_BUZZER, HIGH);
    lcd.setCursor(8, 0); lcd.print("|ALERT! ");
  } else {
    digitalWrite(PIN_BUZZER, LOW);
    lcd.setCursor(8, 0); lcd.print("|CLR:OK ");
  }
}

// 4. VENDING MACHINE (#13)
void handleVending() {
  if (digitalRead(PIN_VEND_BTN) == LOW) {
    if (vendingStock > 0) {
      digitalWrite(PIN_RELAY, HIGH);
      vendingStock--;
      EEPROM.write(0, vendingStock);
      EEPROM.commit();
      Serial.print("VENDING: Dispensing. Stock left: "); Serial.println(vendingStock);
      delay(1000); // Simulate motor running
      digitalWrite(PIN_RELAY, LOW);
    } else {
      Serial.println("VENDING: OUT OF STOCK!");
    }
  }
}

// 5. PARKING OCCUPANCY (#15)
void handleParking() {
  if (digitalRead(PIN_PIR) == HIGH) {
    // This represents the "Bluetooth Data" transfer
    Serial.println("BT_SEND: BAY_OCCUPIED");
  }
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("PARTS COUNT: ");
  lcd.print(partCount);
}
