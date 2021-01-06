#ifndef settings_h
#define settings_h

#include <Arduino.h>

#ifdef __cplusplus
extern "C"{
#endif

int address = 0;
int address1;

float data;

uint16_t dataF;

float coefficient;

uint16_t* tmp = NULL;
uint16_t tmp2, tmp3;

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
  coefficient = coefficient / dataF; 

  EEPROM.put(0,  coefficient );   // coefficient

  EEPROM.put(5, dataF);
}

} 

#endif