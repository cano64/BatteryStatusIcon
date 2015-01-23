
/*


*/

#include "BatteryStatusIcon.h"


BatteryStatusIcon::BatteryStatusIcon(LiquidCrystal *alcd, uint8_t ac, uint16_t low, uint16_t high) : 
  lcd(alcd), c(ac), level(0), percent(0), voltLow(low), voltHigh(high), voltOld(0), voltSchmidt((high-low)/100)
{
	//this->setLevel(0);
}

void BatteryStatusIcon::update(uint16_t volt) {
  //filter out oscillations, the new value must be at least voltSchmidt from the old value
  this->lcd->createChar(this->c, BatteryStatusIcon::batteryStatusIcons[this->level]);
  if (volt >= this->voltOld) {
    if (volt - this->voltOld < this->voltSchmidt) return;
  } else if (volt < this->voltOld) {
    if (this->voltOld - volt < this->voltSchmidt) return;
  }
  if (volt <= this->voltLow) {
    this->setLevel(0);
    this->percent = 0;
  } else if (volt >= this->voltHigh) {
    this->setLevel(BATTERY_STATUS_NUM_STATES-1);
    this->percent = 99; //use 99 as maximum instead of 100 to fit in two digits
  } else {
    this->setLevel(map(volt, this->voltLow, this->voltHigh, 0, BATTERY_STATUS_NUM_STATES-1));
    this->percent = (map(volt, this->voltLow, this->voltHigh, 0, 99));
  }
}


void BatteryStatusIcon::draw() {
  this->lcd->write(this->c);
}


void BatteryStatusIcon::draw(uint8_t x, uint8_t y) {
  this->lcd->setCursor(x, y);
  this->draw();
}


void BatteryStatusIcon::setLevel(uint8_t alevel) {
  if (alevel >= BATTERY_STATUS_NUM_STATES) alevel = BATTERY_STATUS_NUM_STATES-1;
  if (1) {
  //if (this->level != alevel) {
    this->level = alevel;
    this->lcd->createChar(this->c, BatteryStatusIcon::batteryStatusIcons[this->level]);
  }
  if (this->level == 0) { //battery empty, blink
    if ((millis() / 1000) % 2) {
      this->lcd->createChar(this->c, BatteryStatusIcon::batteryStatusIcons[this->level]);
    } else {
      uint8_t empty[8] = {0,0,0,0,0,0,0,0};
      this->lcd->createChar(this->c, empty);
    }
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
    0b10011,
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