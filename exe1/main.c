#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define BTN_PIN_R 28
#define EVENT_FALL GPIO_IRQ_EDGE_FALL
#define EVENT_RISE GPIO_IRQ_EDGE_RISE

volatile bool flag_fall = false;
volatile bool flag_rise = false;

void btn_callback(uint gpio, uint32_t events) {
  if (events & EVENT_FALL) {
    flag_fall = true;
  }
  if (events & EVENT_RISE) {
    flag_rise = true;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  // Enable interrupts for both rising and falling edges
  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, EVENT_RISE | EVENT_FALL, true, &btn_callback);

  while (true) {
    if (flag_fall) {
      printf("fall\n");
      flag_fall = false;
    }

    if (flag_rise) {
      printf("rise\n");
      flag_rise = false;
    }
  }
}
