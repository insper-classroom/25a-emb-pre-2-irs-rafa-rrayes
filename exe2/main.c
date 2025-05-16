#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define LED_PIN 4
#define BTN_PIN 28

volatile bool flag = false;

void btn_callback(uint gpio, uint32_t events) {
  if (events & GPIO_IRQ_EDGE_FALL) {
    flag = !flag;
  }
}

int main() {
  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    gpio_put(LED_PIN, flag);
    tight_loop_contents();
  }
}
