#include "Sensa.h"
#include <dht.h>
#include <SHT1x.h>
#include <Wire.h>
#include <Adafruit_AM2315.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <EEPROM.h>

// API Commands
enum API_commands {
  SAMPLING,
  DWRITE
};
extern byte IO_commands;

Sensa sensa;

void setup() {
  sensa.initializeHighPins();
  Serial.begin(9600);
  Serial1.begin(57600);
  //while(!Serial){delay(1000);}
  Serial.println(F("STARTING"));
}

void loop() {
  if (Serial1.available() > 0) {
    delay(5);
    String cmd  = Serial1.readStringUntil('/');
    //Serial.println(cmd);
    process(cmd);
  }
  delay(50);
}

void process(String cmd) {
  if (cmd == "0") {
    Serial.println(F("SAMPLING"));
    sensa.readSensors();
  }
  else if (cmd == "d") {
    Serial.print(F("DIGITAL "));
    digitalCommand();
  }
  else if (cmd == "activate") {
    activateIO();
  }
  else if (cmd == "deactivate") {
    deactivateIO();
  }
  else if (cmd == "read") {
    Serial.print(F("READ IO "));
    readIO();
  }
  else if (cmd == "write") {
    writeIO();
  }
  else if (cmd == "init") {
    setInitPinStatuses();
  }
}

void readIO(){
  int io_id = Serial1.parseInt();
  if (Serial1.read() != '/') {
      Serial.print(F("ID missing"));
      return;
  }
  sensa.readIO(io_id);
}

void activateIO(){
  int io_id = Serial1.parseInt();
  char delim = Serial1.read();
  if (delim != '/') {
      Serial.print(F("Type missing"));
      return;
  }
  String io_type = Serial1.readStringUntil('/');
  int io_pin = Serial1.parseInt();
  sensa.activateIO(io_id, io_type, io_pin);
  Serial1.println(1);
}

void deactivateIO(){
  int io_id = Serial1.parseInt();
  if (Serial1.read() != '/') {
      Serial.print(F("ID missing"));
      return;
  }
  int io_pin = Serial1.parseInt();
  sensa.deactivateIO(io_id);
  Serial1.println(1);
}

void writeIO(){
  int IO_id, value;
  // Read pin number
  IO_id = Serial1.parseInt();

  if (Serial1.read() != '/') {
    Serial.println(F("Failed to write value"));
    return;
  }
  value = Serial1.parseInt();
  Serial.print(F("Write ID:"));
  Serial.print(IO_id);
  Serial.print(F(", value:"));
  Serial.println(value);
  sensa.writeSwitch(IO_id, value);
}

void digitalCommand(){
  int pin, value;

  // Read pin number
  pin = Serial1.parseInt();

  if (Serial1.read() == '/') {
    value = Serial1.parseInt();
    Serial.print(F("WRITE PIN :"));
    Serial.print(pin);
    Serial.print(F(", VALUE :"));
    Serial.println(value);
    digitalWrite(pin, value);
  }
  else {
    value = digitalRead(pin);
    Serial.print(F("READ PIN :"));
    Serial.println(pin);
    Serial1.println(value);
  }
}

void setInitPinStatuses(){
  int pin = Serial1.parseInt();
  byte value = 0;
  if (Serial1.read() != '/') {
      Serial.print(F("Missing init value. Setting default LOW."));
  }
  else{
    value = Serial1.parseInt();
  }
  sensa.setInitDigitalState(pin, value);
}
