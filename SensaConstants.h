#include <Arduino.h>
// IO Config
#define IO_NUMBER 16
#define IO_FIELDS  5

#define UPDATE_DELAY  4000

#define SHT10_CLOCK 4
// IO Details
enum IO_details {
  STATUS,
  PIN,
  TYPE,
  MODEL,
  N_DATA,
};
extern byte IO_details;

// IO TYPE
enum IO_types {
  SENSOR,
  ACTUATOR
};
extern byte IO_types;

// IO STATUS
enum IO_status {
  INACTIVE,
  ACTIVE,
  ERROR,
};
extern byte IO_status;

// IO MODEL
enum IO_model {
  DEFAULT_MODEL,
  AM2302,
  AM2302T,
  AM2302H,
  AM2315,
  AM2315T,
  AM2315H,
  SHT10,
  SHT10T,
  SHT10H,
  RES_MOIS,
  BIN_SWITCH,
  BIN_RSWITCH,
  DS18B20,
};
extern byte IO_model;
