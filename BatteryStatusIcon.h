

/*

*/

#ifndef BatteryStatusIcon_H
#define BatteryStatusIcon_H


#include "Arduino.h"
#include "LiquidCrystal.h"

#define BATTERY_STATUS_NUM_STATES 6

class BatteryStatusIcon {

  public: 
    static uint8_t batteryStatusIcons[BATTERY_STATUS_NUM_STATES][8];
    LiquidCrystal *lcd;
    uint8_t c;
    uint8_t level;
    uint8_t percent;
    uint16_t voltLow;
    uint16_t voltHigh;
    
    BatteryStatusIcon(LiquidCrystal *alcd, uint8_t ac, uint16_t low, uint16_t high); //the constructor
    void draw();
    void draw(uint8_t x, uint8_t y);
    void setLevel(uint8_t alevel); //set icon number directly example (0, 1, 2, 3...)
    //void setLevel(int val, int min, int max); //set icon number by providing voltage and boundaries example (2523, 2000, 3000)
    void setVoltageInterval(uint16_t low, uint16_t high);
    void update(uint16_t volt);
    //void update();
    
  private:
  
}; //end of class BatteryStatusIcon




#endif
