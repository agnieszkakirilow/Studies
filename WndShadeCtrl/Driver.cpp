#include <Arduino.h>
#include "Driver.h"
#include "Settings.h"
#include "Motor.h"
 

Driver::Driver(Motor* m) :
  _motor(m),
  lightSum(0),
  samples(1),
  decisionBasePeriod(1000 * 20), // 20s
  samplePeriod(1000 * 5)
{
  /// 250
  _sensThresholds[SENS_25] = 200;

  // 500
  _sensThresholds[SENS_50] = 450;

  // 750
  _sensThresholds[SENS_75] = 680;

  // 1000
  _sensThresholds[SENS_100] = 900;
}

void Driver::control(Settings &s)
{
  if (s.mode == MODE_MANUAL) 
  {
    switch(s.dir)
    {
      case DIR_UP:
      {
        _motor->up(32);
        break;
      }
      case DIR_DOWN:
      {
        _motor->down(32);
        break;
      }
      default:
      {
        _motor->brake();
        break;
      }
    }
  }
  else // MODE_AUTO
  {
    // interrupt from limit sensor
    if (s.dir == DIR_STOP)
    {
      _motor->brake();
    }

    if (s.periodicityChanged)
     {
      s.periodicityChanged = false;
      startMillis = millis();
      samples = 1;
      lightSum = 0;
      Serial.print("new periodicity ");
      Serial.println(samples, DEC);
    }
    currentMillis = millis();

    if (currentMillis - startMillis > samplePeriod * samples)
    {
      uint16_t lightCur = analogRead(A2);
      Serial.print("current: ");
      Serial.println(lightCur, DEC);
      lightSum += lightCur;//light sensor
      Serial.print("samples: ");
      Serial.print(samples, DEC);
      Serial.print("   avg: ");
      Serial.print(lightSum, DEC);
      Serial.print("   pos ");
      Serial.println(s.pos, DEC);
      samples++;
    }

    if (currentMillis - startMillis > decisionBasePeriod * s.periodicity)
    {
      Serial.print(currentMillis, DEC);
      Serial.print(" - ");
      Serial.print(startMillis, DEC);
      Serial.print(" > ");
      Serial.print(decisionBasePeriod, DEC);
      Serial.print("   ");
      Serial.println(s.periodicity, DEC);

      uint16_t lightAvg = lightSum / (samples - 1);
      Serial.print("amb: ");
      Serial.println(lightAvg, DEC);
    
      if ((lightAvg < _sensThresholds[s.sensitivity]) && (s.pos != POS_UP))
      {
        Serial.println("auto up");
        s.pos = POS_MIDDLE;
        s.dir = DIR_UP;
        _motor->up(32);
      }
      else if ((lightAvg > _sensThresholds[s.sensitivity]) && (s.pos != POS_DOWN))
      {
        Serial.println("auto down");
        s.pos = POS_MIDDLE;
        s.dir = DIR_DOWN;
        _motor->down(32);
      }
      lightSum = 0;
      samples = 1;
      startMillis = millis();
    }
  } 
}

