#include <LiquidCrystal_I2C.h>  // Include the LCD library

// Pin setup
#define BUZZER_PIN 8       // Buzzer pin
#define MQ2_DO_PIN 7       // Digital output pin from MQ2 sensor

// Initialize the LCD (using I2C)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16 columns, 2 rows (16x2 LCD)

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);  
  lcd.print("Warming up...");
  
  // Set up buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MQ2_DO_PIN, INPUT);  
  digitalWrite(BUZZER_PIN, LOW);

  // Warm-up time for the sensor
  delay(60000);  // 60 seconds
  lcd.clear();
  lcd.print("Gas Sensor Ready");
  delay(2000);
}

void loop() {
  // Read the digital output of the MQ2 sensor
  int gasLevel = digitalRead(MQ2_DO_PIN);  // Read the digital state (HIGH/LOW)

  // Display the gas level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Level:");
  lcd.print(gasLevel);
  
  // If gas is detected, trigger buzzer
  if (gasLevel == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("HIGH");
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on buzzer
    delay(10000);                   // Wait for 10 seconds
    digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("LOW");
  }

  // Debugging information
  Serial.print("Digital Gas Level: ");
  Serial.println(gasLevel);

  delay(1000);  // Wait for 1 second before reading again
}
