#include <SoftwareSerial.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <SD.h>
#include <SPI.h>
#include <Timer.h>

//WiFi and Firebase Auth
#define FIREBASE_HOST "covprev-2021-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "dBtI5rifk02CrNCPpt2xvracGsurTSVc2jhjm96h"
#define WIFI_SSID "8T"
#define WIFI_PASSWORD "aaaaaaaa"

//Timer
Timer timer;

//Global variables
float dataTagCounter;
char dataTagString[100];
char firebaseDataTagStringTemp[200];
char firebaseDataTagStringSPO2[200];
char firebaseDataTagStringPulse[200];
char firebaseDataTagStringTime[200];

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseJson json;

//Pin declarations
SoftwareSerial arduinoSerial(D2, D3); // D3: Rx, D2: Tx
int sdCardCSPin = D8;
int internetStatusLEDPin = D4;
int processLEDPin = D1;

//File objects
File file;
File dataCounterFile;
File myOrigFile;
File myDestFile;
File myNewOrigFile;
File availCheck;

//Time clients
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Working SD Card Files
String offlineDataCSVFile = "covprevOfflineData.csv";
String tempCSVFile = "tempCSVFile.csv";
String dataCounterFileName = "dataCounter.csv";

char offlineDataString[200];

struct sensorDataStruct {
  float dataTagCounter;
  String dataTimestamp;
  float tempReading;
  float spo2Reading;
  float pulseReading;
};

void setup()
{
  pinMode(internetStatusLEDPin, OUTPUT);
  pinMode(processLEDPin, OUTPUT);
  Serial.begin(115200);
  arduinoSerial.begin(9600);
  connectToWiFiAndFirebase();
  initializeSD();
  initializeNTPClient();
  int internetTimer = timer.every(10000, checkPingAndUpdateFirebase);
}

void loop()
{
  timeClient.update();
  
  String rawArduinoData = arduinoSerial.readStringUntil('\n');
//  if (arduinoData != NULL) {
  if (rawArduinoData.charAt(0) == '~'){
    String arduinoData = rawArduinoData.substring(1);
    digitalWrite(processLEDPin, HIGH);

    Serial.print("Data received from Arduino: ");
    Serial.println(arduinoData);

    if (checkPing()) {
      readSerialDataFromArduinoSendToFirebase(arduinoData);
      while (!checkIfFileEmpty(offlineDataCSVFile)) {
        uploadOfflineDataEntryToFirebaseAndDeleteLine(offlineDataCSVFile);
      }
    }
    else {
      writeDataToCSVFile(arduinoData, offlineDataCSVFile);
    }
    digitalWrite(processLEDPin, LOW);
  } else {
    timer.update();
  }
}


void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(sdCardCSPin, OUTPUT);

  if (SD.begin(sdCardCSPin))
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}


int writeToFile(char text[])
{
  if (file)
  {
    file.println(text);
    Serial.print("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(String filename)
{
  file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.print("Error while opening file: ");
    Serial.println(filename);
    return 0;
  } else {
    Serial.print(filename);
    Serial.println(" opened.");
    return 1;
  }
}

String uploadOfflineDataEntryToFirebaseAndDeleteLine(String filename)
{
  openFile(filename);
  String received = "";
  char ch;
  file.seek(0);
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      sendFirstCSVLineToFirebase(received);
      deleteFirstCSVLine(offlineDataCSVFile);
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
}

void sendFirstCSVLineToFirebase(String received) {

  char *token;
  int outputStructCounter = 0;
  const char s[2] = ",";
  char receivedChar[150];
  char csvLineRead[100];
  float csvLineReadInt;

  received.toCharArray(receivedChar, 100);
  token = strtok(receivedChar, s);
  struct sensorDataStruct currentSensorDataStruct;
  while (token != NULL) {
    sprintf(csvLineRead, "%s", token);
    if (outputStructCounter == 0) {
      csvLineReadInt = atof(csvLineRead);
      currentSensorDataStruct.dataTagCounter = csvLineReadInt;
    } else if (outputStructCounter == 1) {
      currentSensorDataStruct.dataTimestamp = csvLineRead;
    } else if (outputStructCounter == 2) {
      csvLineReadInt = atof(csvLineRead);
      currentSensorDataStruct.tempReading = csvLineReadInt;
    } else if (outputStructCounter == 3) {
      csvLineReadInt = atof(csvLineRead);
      currentSensorDataStruct.spo2Reading = csvLineReadInt;
    } else if (outputStructCounter == 4) {
      csvLineReadInt = atof(csvLineRead);
      currentSensorDataStruct.pulseReading = csvLineReadInt;
    }
    token = strtok(NULL, s);
    outputStructCounter++;
  }

  sendDataToFirebase(currentSensorDataStruct.dataTagCounter, currentSensorDataStruct.dataTimestamp, currentSensorDataStruct.tempReading, currentSensorDataStruct.spo2Reading, currentSensorDataStruct.pulseReading);
  closeFile();
}



void sendDataToFirebase(float dataTagCounter, String dataTimestamp, float tempReading, float spo2Reading, float pulseReading) {

  // Create new data tag
  sprintf(dataTagString, "sensorData/%05.0f", dataTagCounter);
  Serial.print("Data Entry Tag Number: " );
  Serial.println(dataTagString);

  Serial.print(F("Timestamp: "));
  Serial.print(dataTimestamp);
  Serial.print(F(" || Temperature: "));
  Serial.print(tempReading);
  Serial.print(F("C || Oxygen Percentage: "));
  Serial.print(spo2Reading);
  Serial.print(F("% || Pulse: "));
  Serial.print(pulseReading);
  Serial.println(F("BPM"));

  sprintf(firebaseDataTagStringTime, "/%s/timestamp", dataTagString);
  if (Firebase.setString(firebaseData, firebaseDataTagStringTime, dataTimestamp))
  {
    Serial.print("TIMESTAMP PASSED || ");
    Serial.println("PATH: " + firebaseData.dataPath());
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  sprintf(firebaseDataTagStringTemp, "/%s/temperature", dataTagString);
  if (Firebase.setFloat(firebaseData, firebaseDataTagStringTemp, tempReading))
  {
    Serial.print("TEMPERATURE PASSED || ");
    Serial.println("PATH: " + firebaseData.dataPath());
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  sprintf(firebaseDataTagStringSPO2, "/%s/spo2", dataTagString);
  if (Firebase.setFloat(firebaseData, firebaseDataTagStringSPO2, spo2Reading))
  {
    Serial.print("SPO2 PASSED || ");
    Serial.println("PATH: " + firebaseData.dataPath());
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  sprintf(firebaseDataTagStringPulse, "/%s/pulse", dataTagString);
  if (Firebase.setFloat(firebaseData, firebaseDataTagStringPulse, pulseReading))
  {
    Serial.print("PULSE PASSED || ");
    Serial.println("PATH: " + firebaseData.dataPath());
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  updateDeviceTimestampToFirebase();
}

void deleteFirstCSVLine(String filename) {
  // Delete First Line of CSV
  myOrigFile = SD.open(filename, FILE_READ);
  char ch;
  while (myOrigFile.available())
  {
    ch = myOrigFile.read();
    if (ch == '\n')
    {
      break;
    }
  }
  int deleteLineData;
  myDestFile = SD.open(tempCSVFile, FILE_WRITE);
  while ((deleteLineData = myOrigFile.read()) >= 0) {
    myDestFile.write(deleteLineData);
  }
  myOrigFile.close();
  SD.remove(offlineDataCSVFile);
  myNewOrigFile = SD.open(filename , FILE_WRITE);

  myDestFile.seek(0);
  while ((deleteLineData = myDestFile.read()) >= 0) {
    myNewOrigFile.write(deleteLineData);
  }
  myNewOrigFile.close();
  myDestFile.close();
  SD.remove(tempCSVFile);
  Serial.println("Data entry removed from CSV file.");
}

int checkIfFileEmpty(String filename) {
  int checkIfFileEmptyInt;
  availCheck = SD.open(filename, FILE_READ);
  checkIfFileEmptyInt = availCheck.read();
  availCheck.close();
  if (checkIfFileEmptyInt == -1) {
    Serial.println("No offline data to be synced.");
    return 1;
  }
  else {
    Serial.println("Unsynced offline data found.");
    return 0;
  }
}

void connectToWiFiAndFirebase() {
  //Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Connect To Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

int checkPing() {
  int pingStatus;
  pingStatus = Ping.ping("https://covprev-2021-default-rtdb.firebaseio.com");
  Serial.print("Connection Status: ");
  Serial.println(pingStatus);
  if (pingStatus) {
    if (digitalRead(internetStatusLEDPin) == LOW) {
      digitalWrite(internetStatusLEDPin, HIGH);
    }
  } else if (digitalRead(internetStatusLEDPin) == HIGH) {
    digitalWrite(internetStatusLEDPin, LOW);
  }
  return pingStatus;
}

void writeDataToCSVFile(String received, String filename) {

  char *token;
  int outputStructCounter = 0;
  const char s[2] = ",";
  char receivedChar[150];
  char arduinoSerialReadChar[100];
  float arduinoSerialReadInt;

  received.toCharArray(receivedChar, 100);
  token = strtok(receivedChar, s);
  struct sensorDataStruct currentSensorDataStruct;

  while (token != NULL) {
    sprintf(arduinoSerialReadChar, "%s", token);
    if (outputStructCounter == 0) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.tempReading = arduinoSerialReadInt/100;
    } else if (outputStructCounter == 1) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.spo2Reading = arduinoSerialReadInt;
    } else if (outputStructCounter == 2) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.pulseReading = arduinoSerialReadInt;
    }
    token = strtok(NULL, s);
    outputStructCounter++;
  }
  currentSensorDataStruct.dataTagCounter = getCurrentDataCounter();
  String timestampReading = getCurrentTimeStamp();

  char offlineDataString[200];
  char timestampReadingArray[20];
  timestampReading.toCharArray(timestampReadingArray, 20);
  sprintf(offlineDataString, "%f,%d,%f,%f,%f", currentSensorDataStruct.dataTagCounter, timestampReadingArray, currentSensorDataStruct.tempReading, currentSensorDataStruct.spo2Reading, currentSensorDataStruct.pulseReading);
  openFile(filename);
  writeToFile(offlineDataString);
  closeFile();
}

float getCurrentDataCounter() {
  dataCounterFile = SD.open("dataCounter.txt", FILE_WRITE);
  if (dataCounterFile) {
    float dataCounterReadFloat;
    String dataCounterReadString = "";
    dataCounterFile.seek(0);
    while (dataCounterFile.available()) {
      char ch;
      ch = dataCounterFile.read();
      dataCounterReadString += ch;
    }
    dataCounterReadFloat = dataCounterReadString.toFloat();
    dataCounterReadFloat++;
    dataCounterFile.seek(0);
    dataCounterFile.println(dataCounterReadFloat);
    dataCounterFile.close();
    Serial.print("New data count CSV: ");
    Serial.println(dataCounterReadFloat);
    return dataCounterReadFloat;
  }
  else {
    dataCounterFile.close();
    Serial.println("Error opening dataCounter.csv | Working with on-board count.");
    dataTagCounter++;
    return dataTagCounter;
  }
}

void initializeNTPClient() {
  timeClient.begin();
  timeClient.setTimeOffset(19800);
}


String getCurrentTimeStamp() {
  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;
  String currentDateTime = formattedTime + " " + String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);
  return currentDateTime;
}

void readSerialDataFromArduinoSendToFirebase(String received) {

  char *token;
  int outputStructCounter = 0;
  const char s[2] = ",";
  char receivedChar[150];
  char arduinoSerialReadChar[100];
  float arduinoSerialReadInt;

  received.toCharArray(receivedChar, 100);
  token = strtok(receivedChar, s);
  struct sensorDataStruct currentSensorDataStruct;

  while (token != NULL) {
    sprintf(arduinoSerialReadChar, "%s", token);
    if (outputStructCounter == 0) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.tempReading = arduinoSerialReadInt/100;
    } else if (outputStructCounter == 1) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.spo2Reading = arduinoSerialReadInt;
    } else if (outputStructCounter == 2) {
      arduinoSerialReadInt = atof(arduinoSerialReadChar);
      currentSensorDataStruct.pulseReading = arduinoSerialReadInt;
    }
    token = strtok(NULL, s);
    outputStructCounter++;
  }
  currentSensorDataStruct.dataTagCounter = getCurrentDataCounter();
  currentSensorDataStruct.dataTimestamp = getCurrentTimeStamp();

  sendDataToFirebase(currentSensorDataStruct.dataTagCounter, currentSensorDataStruct.dataTimestamp, currentSensorDataStruct.tempReading, currentSensorDataStruct.spo2Reading, currentSensorDataStruct.pulseReading);
}

void updateDeviceTimestampToFirebase() {
  Serial.print("Updating timestamp to Firebase... ");
  if (Firebase.setInt(firebaseData, "/deviceStatus/timestamp", timeClient.getEpochTime())) {
    Serial.println("completed.");
  }
  else {
    Serial.println("failed.");
    Serial.println("REASON: " + firebaseData.errorReason());
  }
}

void checkPingAndUpdateFirebase() {
  if (checkPing()) {
    Serial.print("Pinged server. | ");
    updateDeviceTimestampToFirebase();
  }
  else {
    Serial.println("Could not ping the server.");
  }
}
