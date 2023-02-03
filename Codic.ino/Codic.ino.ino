// Code write by @LorenzoVasi on GitHub for controlling Heating System 
// Message Structure:
// Example 1: 24
// Example 2: 24, 32558s
// Example 3: OFF

// Include Libraries
#include "DHT.h"
#include <SoftwareSerial.h>

// Define PINS Connection
#define DHTPIN 2
#define RELAY_PIN 3
#define TX_GSM 4
#define RX_GSM 5
#define PIN_ERR 6
#define PIN_BUT_STOP 7

// Other Definition
#define DHTTYPE DHT22 // Define model of DHT
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial mySerial(TX_GSM, RX_GSM); // Set PINS GSM

// Set Variables
String time = ""; // Define it in second into message, how many time control remote go to ON
bool ControlRemote = false; // Start Control Thermostat when go to true
float temperature = 0.0; // Temperature set into message
bool state_relay = false; // Check status of Relay
float margin = 0.5; // Set margin for not flicking water heater
bool check = true; // If there's problem during inizialization, set false
String message = ""; // Look message
float t = 0.0; // Look Actual Outside Temperature

void setup() {

  // Setup All Sensors

  Serial.begin(9600); // Set Serial Clock
  
  dht.begin(); // Begin DHT Sensor
  // See if “Failed to read from DHT sensor!”

  pinMode(RELAY_PIN, OUTPUT); // Begin Relay as Output 

  pinMode(PIN_ERR, OUTPUT); // Begin PinError as Output

  pinMode(PIN_BUT_STOP, INPUT); // Begin PIN_BUT_STOP as Input

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

  // HERE SET ALL SYSTEMS

  if (check == false) // Someone make error
    digitalWrite(PIN_ERR, HIGH);
    // Print Error into Serial Comunication
  else  
    // Print OK into Serial Comunication
    for (int i = 0; i < 2; i++)
      digitalWrite(PIN_ERR, HIGH);
      delay(500);
      digitalWrite(PIN_ERR, LOW);
      delay(500);
      
}

void loop() {
  // put your main code here, to run repeatedly:

  // Control Message ---------------------
  if (mySerial.available() > 0) // if message is avariable
    if (mySerial.read() == '\n')  // If character '\n', there's a new text line
      message = mySerial.readStringUntil('\n');
      if (message.indexOf(',') != -1 && checkStringIsNumerical(message))  // Caso 1 
        ControlRemote = true;
        temperature = message.toFloat();
      if (message.indexOf(',') != -1 && checkStringIsNumerical(message) == false)
        // Grep message and convert into 2 variables
      if (message.indexOf(',') == -1) // Caso 3
        ControlRemote = false;

  // Control Button Status --------------
  if (digitalRead(PIN_BUT_STOP) == 1) // If someone click stop button
    ControlRemote=false;

  // Control Timing Controller ----------
  if (time != 0)
    // if (after time)
      // ControlRemote false
      // time = 0

  // Control Remote Controller -----------
  if (ControlRemote == true){
    t = dht.readTemperature();
    if (t < temperature-margin)
      if (state_relay == false)
          digitalWrite(RELAY_PIN, HIGH);
          state_relay = true;
    if (t > temperature+margin)
      if (state_relay == true)
        digitalWrite(RELAY_PIN, LOW);
        state_relay = false;
  } else {
    if (state_relay == true)
      digitalWrite(RELAY_PIN, LOW);
      state_relay = false;
  }
  
}


// External Functions ------------------------


// Check is numerical

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}


bool checkStringIsNumerical(String myString) {
  for (int i = 0; i < sizeof(myString); i++) {
    if (!isDigit(myString.charAt(i))) {
      return false;
    }
  }
  return true;
}
