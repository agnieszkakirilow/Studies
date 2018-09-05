#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>

#define MODE_MANUAL 0
#define MODE_AUTO 1

#define POS_DOWN 0
#define POS_MIDDLE 1
#define POS_UP 2

#define DIR_UP 2
#define DIR_DOWN 1
#define DIR_STOP 0

#define SENS_25 0
#define SENS_50 1
#define SENS_75 2
#define SENS_100 3

#define PERIOD_15 1
#define PERIOD_30 2
#define PERIOD_60 4

struct Settings
{
  uint8_t mode:1;
  uint8_t pos:2;
  uint8_t dir:2;
  uint8_t sensitivity:2;
  uint8_t periodicity:3;
  uint8_t periodicityChanged:1;
  uint8_t padding:5;

  Settings() :
    mode(MODE_MANUAL),
    pos(POS_UP),
    dir(DIR_STOP),
    sensitivity(SENS_25),
    periodicity(PERIOD_15),
    periodicityChanged(false)
  {}
};

#endif /* SUNBLINDSETTINGS_H */

