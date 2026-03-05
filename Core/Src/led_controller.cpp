#include "led_controller.h"
#include "stm32f411xe.h"

// Constructor - base config
LedController::LedController(uint32_t pin_num) : pin(pin_num) {
  // PORT C Clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Optional config delay
  volatile uint32_t dummy = RCC->AHB1ENR;
  (void)dummy;

  // Push-Pull pin
  GPIOC->MODER &= ~(3 << (pin * 2));
  GPIOC->MODER |= (1 << (pin * 2));
}

void LedController::toggle() { GPIOC->ODR ^= (1 << pin); }

void LedController::on() {
  // state LOW for LED ON
  GPIOC->BSRR = (1 << (pin + 16));
}

void LedController::off() {
  // state HIGH for LED OFF
  GPIOC->BSRR = (1 << pin);
}