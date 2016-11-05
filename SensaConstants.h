#include <Arduino.h>
// IO Config
#define IO_NUMBER 16
#define IO_FIELDS  5

#define UPDATE_DELAY  4000

#define SHT10_CLOCK 4

//MG-811
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier

#define         READ_SAMPLE_TIMES            (10)     //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_INTERVAL         (50)    //define the time interval(in milisecond) between each samples in

//These values differ from sensor to sensor. User should derermine this value.
#define         ZERO_POINT_X                 (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         MAX_POINT_VOLTAGE            (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define         REACTION_VOLTAGE             (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

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
  DS18B20_1,
  LDR,
  BH1750,
  MG811,
};
extern byte IO_model;
