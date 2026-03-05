#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H
#include <stdint.h>

class LedController {
private:
  uint32_t pin;

public:
  LedController(uint32_t pin_num);

  void toggle();
  void on();
  void off();
};

#endif