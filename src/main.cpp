#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <MsTimer2.h>

#include <settings.h>

#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
 
modbusDevice regBank;
modbusSlave slave;

void senswater() 
{
  ImpWater = micros() - lastImpWater;                          // Вычислить время между двумя оборотами
  lastImpWater = micros();                                     // Запомнить время последнего оборота
}

void setup()
{
  regBank.setId(1);
  
  regBank.add( 30001 );     regBank.add( 30006 );     regBank.add( 30011 );     regBank.add( 40004 );     regBank.add( 40016 );
  regBank.add( 30002 );     regBank.add( 30007 );     regBank.add( 30012 );     regBank.add( 40005 );               
  regBank.add( 30003 );     regBank.add( 30008 );     regBank.add( 40001 );     regBank.add( 40006 );                    
  regBank.add( 30004 );     regBank.add( 30009 );     regBank.add( 40002 );     regBank.add( 40007 );                  
  regBank.add( 30005 );     regBank.add( 30010 );     regBank.add( 40003 );     regBank.add( 40008 ); 
                                                                                    
  slave._device = &regBank;  
  slave.setBaud(9600);

  pinMode(13, OUTPUT);

  attachInterrupt(0, senswater, RISING);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);    lcd.print(" Hz  ");
  lcd.setCursor(15, 0);   lcd.print(" m3/h");
}

// void writeEEPROM () 
// {
//   EEPROM.put(address,  dataF);
// }

void dataTransfer ( int registr, float out) 
{
  tmp = (uint16_t*) &out;
  regBank.set( 30000 + registr, (word) *tmp);   
  regBank.set( 30000 + registr + 1 , (word) *(tmp + 1));
}

// uint16_t dataReception( int registr)
// {
//   uint8_t tmp2 = regBank.get( 40000 + registr ) ;
//   uint8_t tmp3 = regBank.get( 40000 + registr + 1 );
 
//   return dataF = tmp2 << 8 | tmp3;
// }

void loop() {
  
  data = regBank.get(40001);
  
  if( data == 25)
  {
    // calibration_settings();
    // //dataReception(16);
    coefficient = regBank.get(40002);
    dataF = regBank.get(40003);
    digitalWrite(13, HIGH);  
    writeEEPROM();
    delay(100);
    data = 0;
    digitalWrite(13, LOW);
    regBank.set(40001, 0);
    //regBank.set(40002, 0);
    //regBank.set(40003, 0);
  }

    if (micros() - lastImpWater > 1200000) {                     // Если сигнала нет больше секунды
    ImpWater_freg = 0;                                         // Считаем, что всё стоит и не крутится
    Volume_Water = 0;
  } 

  else {
    time_sek_Water = (float) ImpWater * 0.000001;              // Время одного оборота в секундах
 
    ImpWater_freg = (float) 1 / time_sek_Water;                // Частота оборотов 
    Volume_Water = (float) 3.6 * ImpWater_freg * coefficient;                // Расход м3/ч.
  }

  dataTransfer (1,  EEPROM.get(0, coefficient));
  dataTransfer (3,  EEPROM.get(20, dataF));

  slave.run();

  if (millis() - lastshow > 300) {                                 // Кадждые 300 миллисекунд
   
    lcd.setCursor(0, 0);   lcd.print(ImpWater_freg); lcd.print(spaces);
    lcd.setCursor(5, 0);   lcd.print(" Hz  ");
    lcd.setCursor(10, 0);  lcd.print(Volume_Water);  lcd.print(spaces);
    lcd.setCursor(15, 0);  lcd.print(" m3/h");

    lastshow = millis();
  }
}




