# Sensa controller for Arduino

Provides a common interface to read sensors and write actuators
connected to the Arduino.
The serial connection is used to access the interface with a custom
protocol. Sensors must be activated before sampling data.

## Serial protocol

* Activate I/O
 
 ```activate/<IO_ID>/<IO_TYPE>/ ```
 
* Read I/O

 ```read/<IO_ID>/ ```
 
* Write I/O

  ```write/<IO_ID>/<value>/ ```
  
* Deactivate I/O

  ```deactivate/<IO_ID>/ ```
  
* Set initial status on pin

  ```init/<pin>/<value>/ ```
  
* Sample all registered IOs

  ```0 ```

## I/O Types

*  AM2302T
*  AM2302H
*  AM2315
*  AM2315T
*  AM2315H
*  SHT10T
*  SHT10H
*  RES_MOIS
*  BIN_SWITCH
*  BIN_RSWITCH
*  DS18B20
*  LDR
