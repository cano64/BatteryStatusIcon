
/*


*/

#include "BatteryStatusIcon.h"


BatteryStatusIcon::BatteryStatusIcon(LiquidCrystal *alcd, uint8_t ac) : lcd(alcd), c(ac), level(0), voltLow(1000), voltHigh(3000) {

}

void BatteryStatusIcon::update(uint16_t volt) {
  if (volt <= this->voltLow) {
    this->setLevel(0);
  } else if (volt >= this->voltHigh) {
    this->setLevel(BATTERY_STATUS_NUM_STATES-1);
  } else {
    this->setLevel(map(volt, this->voltLow, this->voltHigh, 0, BATTERY_STATUS_NUM_STATES-1));
  }
}


void BatteryStatusIcon::draw() {
  this->lcd->write(this->c);
}


void BatteryStatusIcon::setLevel(uint8_t alevel) {
  if (alevel >= BATTERY_STATUS_NUM_STATES) alevel = BATTERY_STATUS_NUM_STATES-1;
  if (this->level != alevel) {
    this->level = alevel;
    this->lcd->createChar(this->c, BatteryStatusIcon::batteryStatusIcons[this->level]);
  }
}


void BatteryStatusIcon::setVoltageInterval(uint16_t low, uint16_t high) {
  this->voltLow = low;
  this->voltHigh = high;
}


uint8_t BatteryStatusIcon::batteryStatusIcons[BATTERY_STATUS_NUM_STATES][8] = {

  {
    0b01110,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111
  },
  {
    0b01110,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b11111
  },
  {
    0b01110,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b11111,
    0b11111
  },
  {
    0b01110,
    0b11111,
    0b10001,
    0b10001,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  },
  {
    0b01110,
    0b11111,
    0b10001,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  },
  {
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  }
  
  
};



//