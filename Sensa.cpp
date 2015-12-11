#include "Sensa.h"

#include <Adafruit_AM2315.h>
#include <Arduino.h>
#include <DallasTemperature.h>
#include <dht.h>
#include <OneWire.h>
#include <SHT1x.h>
#include <Wire.h>
#include <EEPROM.h>

Sensa::Sensa(){
  init();
}

Sensa::~Sensa(){}

void Sensa::init(){
  memset(IO, 0, sizeof(IO));
  memset(IO_updates, 0, sizeof(IO_updates));
  memset(IO_values, 0, sizeof(IO_values));
  Wire.begin();
}

void Sensa::activateIO(byte id, String model, byte pin){
  model.toUpperCase();
  if(model == "AM2302"){
    Serial.print(F("Activating AM2302 on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2302;
    IO[id][PIN]    = pin;
  }
  if(model == "AM2302T"){
    Serial.print(F("Activating AM2302T on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2302T;
    IO[id][PIN]    = pin;
  }
  if(model == "AM2302H"){
    Serial.print(F("Activating AM2302H on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2302H;
    IO[id][PIN]    = pin;
  }
  else if(model == "AM2315"){
    Serial.print(F("Activating AM2315 on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2315;
    IO[id][PIN]    = pin;
  }
  else if(model == "AM2315T"){
    Serial.print(F("Activating AM2315T on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2315T;
    IO[id][PIN]    = pin;
  }
  else if(model == "AM2315H"){
    Serial.print(F("Activating AM2315H on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = AM2315H;
    IO[id][PIN]    = pin;
  }
  else if(model == "SHT10"){
    Serial.print(F("Activating SHT10 on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = SHT10;
    IO[id][PIN]    = pin;
  }
  else if(model == "SHT10T"){
    Serial.print(F("Activating SHT10T on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = SHT10T;
    IO[id][PIN]    = pin;
  }
  else if(model == "SHT10H"){
    Serial.print(F("Activating SHT10H on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = SHT10H;
    IO[id][PIN]    = pin;
  }
  else if(model == "RES_MOIS"){
    Serial.print(F("Activating Moisture Sensor on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = RES_MOIS;
    IO[id][PIN]    = pin;
  }
  else if(model == "BIN_SWITCH"){
    Serial.print(F("Activating Binary Switch on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = ACTUATOR;
    IO[id][MODEL]  = BIN_SWITCH;
    IO[id][PIN]    = pin;
    pinMode(pin, OUTPUT);
  }
  else if(model == "BIN_RSWITCH"){
    Serial.print(F("Activating Reversed Binary Switch on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][STATUS] = ACTIVE;
    IO[id][TYPE]   = ACTUATOR;
    IO[id][MODEL]  = BIN_RSWITCH;
    IO[id][PIN]    = pin;
    pinMode(pin, OUTPUT);
  }
  else if(model == "DS18B20"){
    Serial.print(F("Activating DS18B20 sensor on pin "));
    Serial.print(pin);
    Serial.print(F(" with ID "));
    Serial.println(id);
    IO[id][TYPE]   = SENSOR;
    IO[id][MODEL]  = DS18B20;
    IO[id][PIN]    = pin;
    if(IO[id][STATUS] != ACTIVE){
      OneWire oneWire(pin);
      ds_sensors.setOneWire(&oneWire);
      ds_sensors.begin();
      ds_sensors.setResolution(12);
    }
    IO[id][STATUS] = ACTIVE;
    readDS18B20(id);
  }
}

void Sensa::readSensors(){
  for(byte IO_id = 0; IO_id <= IO_NUMBER; IO_id++){
    if(IO[IO_id][TYPE] == SENSOR && IO[IO_id][STATUS] == ACTIVE){
      readIO(IO_id);
      Serial1.print((int)(IO_values[IO_id]*100));
      Serial1.print(F(","));
    }
  }
  Serial1.println();
}

void Sensa::deactivateIO(byte id){
  Serial.print(F("Deactivating IO "));
  Serial.println(id);
  IO[id][STATUS] = INACTIVE;
}

void Sensa::readIO(byte IO_id){
  Serial.print(F("ID "));
  Serial.print(IO_id);
  Serial.print(F(": "));
  switch(IO[IO_id][MODEL]){
    case AM2302:
      Serial.println(F("Reading AM2302"));
      readAM2302(IO_id);
      break;
    case AM2302T:
      Serial.println(F("Reading AM2302T"));
      readAM2302(IO_id);
      break;
    case AM2302H:
      Serial.println(F("Reading AM2302H"));
      readAM2302(IO_id);
      break;
    case AM2315:
      Serial.println(F("Reading AM2315"));
      readAM2315(IO_id);
      break;
    case AM2315T:
      Serial.println(F("Reading AM2315T"));
      readAM2315(IO_id);
      break;
    case AM2315H:
      Serial.println(F("Reading AM2315H"));
      readAM2315(IO_id);
      break;
    case SHT10:
      Serial.println(F("Reading SHT10"));
      readSHT10(IO_id);
      break;
    case SHT10T:
      Serial.println(F("Reading SHT10T"));
      readSHT10(IO_id);
      break;
    case SHT10H:
      Serial.println(F("Reading SHT10H"));
      readSHT10(IO_id);
      break;
    case RES_MOIS:
      Serial.println(F("Reading MOISTURE"));
      readMoisture(IO_id);
      break;
    case DS18B20:
      Serial.println(F("Reading DS18B20"));
      readDS18B20(IO_id);
      break;
  }
}

int Sensa::searchType(byte model){
  for(byte IO_id = 0; IO_id < IO_NUMBER; IO_id++){
    if(IO[IO_id][MODEL] == model){
      return IO_id;
    }
  }
  return -1;
}

void Sensa::readAM2302(byte IO_id){
  if((millis() - IO_updates[IO_id]) < UPDATE_DELAY){
    return;
  }
  dht DHT;
  byte pin = IO[IO_id][PIN];
  int chk = DHT.read22(pin);
  int temp_id, humi_id;
  if(IO[IO_id][MODEL] == AM2302T){
    temp_id = IO_id;
    humi_id = searchType(AM2302H);
  }
  else{
    humi_id = IO_id;
    temp_id = searchType(AM2302T);
  }
  switch (chk)
  {
    case DHTLIB_OK:
      IO_values[temp_id] = DHT.temperature;
      IO_values[humi_id] = DHT.humidity;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print(F("DHT Checksum error\n"));
      // Data may still be valid
      IO_values[temp_id] = DHT.temperature;
      IO_values[humi_id] = DHT.humidity;
      return;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print(F("DHT Time out error\n"));
      break;
    default:
      Serial.print(F("DHT Unknown error\n"));
      break;
  }
  IO_updates[humi_id] = millis();
  IO_updates[temp_id] = IO_updates[humi_id];
}

void Sensa::readAM2315(byte IO_id){
  if((millis() - IO_updates[IO_id]) < UPDATE_DELAY){
    return;
  }
  byte temp_id, humi_id;
  if(IO[IO_id][MODEL] == AM2315T){
    temp_id = IO_id;
    humi_id = searchType(AM2315H);
  }
  else{
    humi_id = IO_id;
    temp_id = searchType(AM2315T);
  }
  Adafruit_AM2315 am2315; // Yun(Leonardo) I2C pins: 2(SDA), 3(SCL)
  if (! am2315.begin()) {
     Serial.println(F("AM2315 not found."));
     IO_values[temp_id] = -1;
     IO_values[humi_id] = -1;
     return;
  }
  am2315.readTemperatureAndHumidity(IO_values[temp_id], IO_values[humi_id]);
  IO_updates[humi_id] = millis();
  IO_updates[temp_id] = IO_updates[humi_id];
}

void Sensa::readSHT10(byte IO_id){
  if((millis() - IO_updates[IO_id]) < UPDATE_DELAY){
    return;
  }
  byte temp_id, humi_id;
  if(IO[IO_id][MODEL] == SHT10T){
    temp_id = IO_id;
    humi_id = searchType(SHT10H);
  }
  else{
    humi_id = IO_id;
    temp_id = searchType(SHT10T);
  }
  SHT1x sht10(IO[IO_id][PIN], SHT10_CLOCK);
  delay(5);
  IO_values[temp_id] = sht10.readTemperatureC();
  IO_values[humi_id] = sht10.readHumidity();
  IO_updates[humi_id] = millis();
  IO_updates[temp_id] = IO_updates[humi_id];
}

void Sensa::readMoisture(byte id){
  int moist = analogRead(IO[id][PIN]);
  int nmoist = round(moist/9.5);
  IO_values[id] = nmoist;
}

void Sensa::readDS18B20(byte id){
  OneWire oneWire(IO[id][PIN]);
  ds_sensors.setOneWire(&oneWire);
  ds_sensors.requestTemperatures();
  IO_values[id] = ds_sensors.getTempCByIndex(0);
  delay(1000);
}

void Sensa::writeSwitch(byte id, byte value){
  bool reversed = false;
  if((IO[id][TYPE] != ACTUATOR) || (IO[id][STATUS] != ACTIVE)) return;
  if((IO[id][MODEL] != BIN_SWITCH) && (IO[id][MODEL] != BIN_RSWITCH)) return;
  if(IO[id][MODEL] == BIN_RSWITCH) reversed = true;
  if(reversed)
    if(value == 1)
      value = 0;
    else
      value = 1;
  digitalWrite(IO[id][PIN], value);

  Serial.print(F("Set pin "));
  Serial.print(IO[id][PIN]);
  if(value == 1)
    Serial.println(F(" HIGH."));
  else
    Serial.println(F(" LOW."));
}

void Sensa::initializeHighPins(){
    //Serial.println(F("Initializing Digital Pins"));
    unsigned int default_DOs;
    EEPROM.get(0, default_DOs);
    for(byte i = 0; i<16; i++){
        if(default_DOs & (1 << i)){
            //Serial.print(F("Turn HIGH ID "));
            //Serial.println(i);
            digitalWrite(i, HIGH);
        }
        if(default_DOs <= (1 << i)) break;
    }
}

void Sensa::setInitDigitalState(byte pin, byte value){
  unsigned int default_DOs, new_default_DOs;
  EEPROM.get(0, default_DOs);
  if(value==0){
    new_default_DOs = default_DOs & ~(1 << pin);
    Serial.print(F("Default value LOW on pin "));
    Serial.println(pin);
  }
  else{
    new_default_DOs = default_DOs | (1 << pin);
    Serial.print(F("Default value HIGH on pin "));
    Serial.println(pin);
  }
  if(new_default_DOs != default_DOs){
    EEPROM.put(0, new_default_DOs);
  }
  else{
    Serial.println(F("Initializer unchanged"));
  }
}
