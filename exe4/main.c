#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define BTN_PIN_R 28
#define BTN_PIN_G 26
#define LED_PIN_R 4
#define LED_PIN_G 6

#define EDGE_FALL GPIO_IRQ_EDGE_FALL
#define EDGE_RISE GPIO_IRQ_EDGE_RISE

volatile bool flag_r = false;
volatile bool flag_g = false;

// Interrupt callback function
void btn_callback(uint gpio, uint32_t events) {
  if ((gpio == BTN_PIN_R) && (events & EDGE_FALL)) {
    flag_r = !flag_r;
  }
  if ((gpio == BTN_PIN_G) && (events & EDGE_RISE)) {
    flag_g = !flag_g;
  }
}

int main() {
  stdio_init_all();

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, EDGE_FALL | EDGE_RISE, true, &btn_callback);

  gpio_set_irq_enabled(BTN_PIN_G, EDGE_FALL | EDGE_RISE, true);

  while (true) {
    gpio_put(LED_PIN_R, flag_r);
    gpio_put(LED_PIN_G, flag_g);
  }
}
