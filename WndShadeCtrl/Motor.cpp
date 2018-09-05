#include "Motor.h"
#include <Arduino.h>

Motor::Motor() 
{
}

Motor::Motor(uint8_t pwm, uint8_t inA1, uint8_t inA2) : 
_pwm(pwm), _inA1(inA1), _inA2(inA2)
{
  pinMode(pwm, OUTPUT);  //pin configuration pin number, mode (input/output)
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);  
}

Motor::~Motor() 
{
}

void Motor::up(uint8_t speed)
{
  digitalWrite(_inA1, HIGH);//write digital value to pin
  digitalWrite(_inA2, LOW);
  analogWrite(_pwm, speed);//write analog value to pin
}

void Motor::down(uint8_t speed)
{
  digitalWrite(_inA1, LOW);
  digitalWrite(_inA2, HIGH);
  analogWrite(_pwm, speed);
}
    
void Motor::brake()
{
  digitalWrite(_inA1, LOW);
  digitalWrite(_inA2, LOW);
}

