#ifndef DRIVER_H
#define DRIVER_H

class Settings;
class Motor;

class Driver
{
public:
  Driver(Motor* m);
  void control(Settings &s);
private:
  Motor* _motor;
  unsigned long startMillis;
  unsigned long currentMillis;
  unsigned long decisionBasePeriod;// = 900000; //15m in ms
  unsigned long samplePeriod;// = 30000; //30s in ms
  uint8_t samples;
  int lightSum;

  int _sensThresholds[4];
};

#endif
