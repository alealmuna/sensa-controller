/**
 * @file Sensa.h
 *
 * Sensa Library
 *
 */
#ifndef __SENSA_H__
#define __SENSA_H__

#include "SensaConstants.h"
#include <Arduino.h>
#include <DallasTemperature.h>

class Sensa {

public:
  Sensa();
  ~Sensa();
  void readSensors();
  void activateIO(byte, String, byte);
  void deactivateIO(byte);
  void readIO(byte);
  void writeSwitch(byte, byte);
  void setInitDigitalState(byte, byte);
  void initializeHighPins();

private:
  void init();
  void readAM2302(byte);
  void readAM2315(byte);
  void readMoisture(byte);
  void readSHT10(byte);
  void readDS18B20(byte);
  int searchType(byte);

  int IO[IO_NUMBER][IO_FIELDS] = {};
  unsigned long IO_updates[IO_NUMBER] = {};
  float IO_values[IO_NUMBER] = {};
  DallasTemperature ds_sensors;
};

#endif // __SENSA_H__:
