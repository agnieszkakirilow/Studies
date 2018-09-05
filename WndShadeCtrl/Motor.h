#ifndef MOTOR_H
#define MOTOR_H

#include <inttypes.h>

class Motor {
public:
  Motor();
  Motor(uint8_t pwm, uint8_t inA1, uint8_t inA2);
  virtual ~Motor();
        
  void up(uint8_t speed);
  void down(uint8_t speed);
  void brake();
private:
  uint8_t _pwm;
  uint8_t _inA1;
  uint8_t _inA2;
};

#endif /* MOTOR_H */

