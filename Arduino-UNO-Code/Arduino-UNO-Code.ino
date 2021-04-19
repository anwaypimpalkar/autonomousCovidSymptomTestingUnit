#include "MAX30100_PulseOximeter.h"
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_MLX90614.h>

//Pin definitions
int sprayRelay = 12;
int sprayTrigger = 9;
int greenLED = 11;
int redLEDBuzzer = 10;

//LCD Display
LiquidCrystal lcd(8, 3, 4, 5, 6, 7);

//Pulse Oximeter Sensor (MAX30100)
PulseOximeter pox;
#define poxReportingPeriod 1000
uint32_t poxLastReport = 0;

//Temperature Sensor (MLX90614)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//Sanitization Spray
#define sprayDelayDuration 5000
#define userSessionTimeout 20000
#define sprayDuration 500
uint32_t lastUserAction = 0;



// Global variables
int allowReadings;
int consoleMode = 1   ;
int showMainScreen = 1;
int showComputingScreen = 1;
int showReadyScreen = 1;
int lastBPMReading = 0;
float lastTempReading = 0;
int readingCounter = 0;
int averageBPM = 0;
int averageSpO2 = 0;
float averageTemp = 0;

void setup() {
  Serial.begin(9600);

  //Initialize display and sensors
  lcd.begin(16, 2);
  lcd.print("LCD INITIALIZED!");
  lcd.setCursor(0, 1);

  //Initialize the pulse oximeter sensor
  lcd.print("INITIALIZING POX");
  while (!pox.begin()) {
    if (consoleMode == 1) {
      Serial.print(".");
    }
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  lcd.clear();
  lcd.print("POX INITIALIZED!");
  lcd.setCursor(0, 1);

  //Initialize the temperature sensor
  lcd.print("INITIALIZING TEM");
  mlx.begin();

  //Set digital pins
  pinMode(sprayRelay, OUTPUT);
  pinMode(sprayTrigger, INPUT);
  pinMode(redLEDBuzzer, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(sprayRelay, HIGH);
  allowReadings = 0;
}

void loop() {

  // Show the welcome screen
  if (showMainScreen == 1) {
    mainScreenLCD();
  }

  // Sanitizer spray
  // Sanitizer spray will be disactivated for a couple seconds after it has been used.
  int sprayTriggerState = !digitalRead(sprayTrigger);
  if (sprayTriggerState == 1 and millis() - lastUserAction > sprayDelayDuration) {
    uint32_t initMillis = millis();
    showKeepHandsCloseScreen();
    while (millis() <= initMillis + 1000) {
      pox.update();
    }
    digitalWrite(sprayRelay, LOW);
    while (millis() <= initMillis + 1000 + 500) {
      pox.update();
    }
    digitalWrite(sprayRelay, HIGH);
    lastUserAction = millis();
    showKeepFingerOnSensorsScreen();
    allowReadings = 1;
  }

  if (millis() - lastUserAction > userSessionTimeout and allowReadings == 1) {
    allowReadings = 0;
    showMainScreen = 1;
  }

  //Get readings from the sensors
  float tempReading = mlx.readObjectTempF() + 10.50;
  int BPM = pox.getHeartRate();
  int SpO2 = pox.getSpO2();
  pox.update();

  //Activate for debugging
  if (consoleMode == 1) {
    Serial.print(sprayTriggerState);
    Serial.print(" | ");
    Serial.print(allowReadings);
    Serial.print(" | ");
    Serial.print(BPM);
    Serial.print(" | ");
    Serial.print(SpO2);
    Serial.print(" | ");
    Serial.print(tempReading);
    Serial.print(" | ");
    Serial.print(lastBPMReading);
    Serial.print(" | ");
    Serial.println(lastTempReading);
  }

  //Initialize the pulse oximeter sensors if the temperature sensor detects an input
  if (tempReading > 95) {
    lastUserAction = millis();
    if (showReadyScreen == 1) {
      if (allowReadings == 1) {
        readyScreenLCD();
        showReadyScreen = 0;
      }
      else {
        showSanitizeFirstScreen();
      }
    }
  }

  if (readingCounter > 0 and tempReading > 90 and showComputingScreen == 1) {
    computingScreenLCD();
    showComputingScreen = 0;
  }

  if (millis() - poxLastReport > poxReportingPeriod) {
    //Add to the readings to the average reading
    if (allowReadings == 1 and BPM >= 60 and BPM <= 140 and SpO2 >= 90 and SpO2 <= 100 and tempReading > 95 and tempReading < 105  and BPM != lastBPMReading and tempReading != lastTempReading  ) {
      readingCounter++;
      lastBPMReading = BPM;
      lastTempReading = tempReading;
      averageBPM = averageBPM + BPM;
      averageSpO2 = averageSpO2 + SpO2;
      averageTemp = averageTemp + tempReading;
      if (consoleMode == 1) {
        Serial.print("COUNTER: ");
        Serial.println(readingCounter);
        Serial.print("AVERAGE: ");
        Serial.print(averageBPM);
        Serial.print(" | ");
        Serial.print(averageSpO2);
        Serial.print(" | ");
        Serial.println(averageTemp);
      }
      lcd.print(".");
    }
    poxLastReport = millis();
  }

  if (readingCounter == 5) {
    averageBPM = averageBPM / 5;
    averageSpO2 = averageSpO2 / 5;
    averageTemp = averageTemp / 5.00;
    if (consoleMode == 1) {
      Serial.print("FINAL AVERAGE: ");
      Serial.print(averageBPM);
      Serial.print(" | ");
      Serial.print(averageSpO2);
      Serial.print(" | ");
      Serial.println(averageTemp);
    }
    char nodeMCUData[50];
    int printableAvgTemp = averageTemp * 100;
    sprintf(nodeMCUData, "~%i,%i,%i", printableAvgTemp, averageSpO2, averageBPM);
    Serial.println(nodeMCUData);
    displayReadingsLCD(averageBPM, averageSpO2, averageTemp, 4000);

    if (averageBPM >= 60 and averageBPM <= 110 and averageSpO2 >= 93 and averageSpO2 <= 100 and averageTemp <= 99) {
      showAcceptableScreenAndActions();
    }
    else {
      showRejectedScreenAndActions();
    }
    readingTimeout();
    BPM = 0;
    SpO2 = 0;
    tempReading = 0;
  }
}

void readingTimeout() {
  readingCounter = 0;
  averageBPM = 0;
  averageSpO2 = 0;
  averageTemp = 0;
  lastBPMReading = 0;
  lastTempReading = 0;
  showMainScreen = 1;
  showComputingScreen = 1;
  showReadyScreen = 1;
}

void mainScreenLCD() {
  lcd.clear();
  lcd.print("    Cov-Prev    ");
  lcd.setCursor(0, 1);
  lcd.print("CovidSymptomTest");
  showMainScreen = 0;
}

void readyScreenLCD() {
  lcd.clear();
  lcd.print("    Cov-Prev    ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing....");
}

void computingScreenLCD() {
  lcd.clear();
  lcd.print("    Cov-Prev    ");
  lcd.setCursor(0, 1);
  lcd.print(" Computing");
}

void displayReadingsLCD(int averageBPM, int averageSpO2, float averageTemp, int displayTime) {
  lcd.clear();
  lcd.print("BPM:");
  lcd.print(averageBPM);
  lcd.print(" SpO2:");
  lcd.print(averageSpO2);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(averageTemp);
  lcd.print(" F");
  delay(displayTime);
}

void showSanitizeFirstScreen() {
  lcd.clear();
  lcd.print(" Sanitize Hands ");
  lcd.setCursor(0, 1);
  lcd.print("     First!     ");
  delay(2000);
  mainScreenLCD();
  showMainScreen = 1;
}

void showKeepFingerOnSensorsScreen() {
  lcd.clear();
  lcd.print("  Place Finger  ");
  lcd.setCursor(0, 1);
  lcd.print("   On Sensors   ");
}

void showKeepHandsCloseScreen() {
  lcd.clear();
  lcd.print("Keep Hands Close");
  lcd.setCursor(0, 1);
  lcd.print("To The Sanitizer");
}

void showAcceptableScreenAndActions() {
  lcd.clear();
  lcd.print(" READINGS OKAY! ");
  lcd.setCursor(0, 1);
  lcd.print(" Data Uploaded. ");
  digitalWrite(greenLED, HIGH);
  delay(5000);
  digitalWrite(greenLED, LOW);
  mainScreenLCD();
  showMainScreen = 1;
}

void showRejectedScreenAndActions() {
  lcd.clear();
  lcd.print("  ENTRY DENIED  ");
  lcd.setCursor(0, 1);
  lcd.print(" Data Uploaded. ");
  digitalWrite(redLEDBuzzer, HIGH);
  delay(5000);
  digitalWrite(redLEDBuzzer, LOW);
  mainScreenLCD();
  showMainScreen = 1;
}
