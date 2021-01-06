#ifndef settings_h
#define settings_h

#include <Arduino.h>

#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

#ifdef __cplusplus
extern "C"{
#endif

int address = 0;
int address1;

float data;

uint16_t dataF, coefficient;

uint16_t* tmp = NULL;

float time_sek_Water, ImpWater_freg, Volume_Water, SumVol_Water, Average_vol_water;

volatile unsigned long  ImpWater, lastImpWater, lastshow;
String spaces = "       ";

// void calibration_settings ()
// {
//     //dataReception(16);
//     dataF = regBank.get(40002);
//     digitalWrite(13, HIGH);  
//     //writeEEPROM();
//     delay(100);
//     data = 0;
//     digitalWrite(13, LOW);
//     regBank.set(40001, 0);
//     regBank.set(40002, 0);
// // 
// }

void writeEEPROM () 
{
  EEPROM.put(0,  coefficient);

  EEPROM.put(20, dataF);
}

} 

#endif