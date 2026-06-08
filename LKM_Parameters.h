#ifndef __LKM_PARAMETERS_H__
#define __LKM_PARAMETERS_H__
#pragma once
#include <map>

#include "Arduino.h"

/*
Constant Parameters for combination of NTU ASR board + Teensy 4.0
*/

// MAX baurate
#define DEFAULT_BAUDRATE 4000000
#define MEDIUM_BAUDRATE 2000000
enum serialPort {
  ID1 = 1,        //
  ID2,            //
  ID3,            //
  ID4,            //
  ID5,            //
  ID6,            //
  ID7,            //
  MAX_SERIAL_ID,  //
};

const std::map<uint8_t, HardwareSerial*> SERIAL_MAP = {
    {ID1, &Serial1},  //
    {ID2, &Serial2},  //
    {ID3, &Serial3},  //
    {ID4, &Serial4},  //
    {ID5, &Serial5},  //
    {ID6, &Serial6},  //
    {ID7, &Serial7},  //
};

const std::map<uint8_t, uint8_t> SERIAL_DE_PIN = {
    {ID3, 13},  //
    {ID5, 2},   //

};

#endif