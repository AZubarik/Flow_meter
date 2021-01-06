#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

modbusDevice regBank;
modbusSlave slave;

void setup() {
  regBank.setId(1);
  
  regBank.add( 30001 );     regBank.add( 30006 );     regBank.add( 30011 );     regBank.add( 40004 ); 
  regBank.add( 30002 );     regBank.add( 30007 );     regBank.add( 30012 );     regBank.add( 40005 );               
  regBank.add( 30003 );     regBank.add( 30008 );     regBank.add( 40001 );     regBank.add( 40006 );                    
  regBank.add( 30004 );     regBank.add( 30009 );     regBank.add( 40002 );     regBank.add( 40007 );                  
  regBank.add( 30005 );     regBank.add( 30010 );     regBank.add( 40003 );     regBank.add( 40008 );
                                                                                    
  slave._device = &regBank;  
  slave.setBaud(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("m3/h");
  lcd.setCursor(0, 1);
  lcd.print("");
}

void loop() {
  // put your main code here, to run repeatedly:
}