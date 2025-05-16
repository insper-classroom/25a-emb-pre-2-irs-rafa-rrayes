#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int PIN_R = 28;
const int PIN_G = 26;

volatile int FLAG_R = 0;
volatile int FLAG_G = 0;

void callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // edge
    
    if (gpio == PIN_R) {
      FLAG_R = 1;
    }

    else if (gpio == PIN_G) {
      FLAG_G = 1;
    }

  }
}

int main() {
  stdio_init_all();

  gpio_init(PIN_R);
  gpio_set_dir(PIN_R, GPIO_IN);
  gpio_pull_up(PIN_R);

  gpio_init(PIN_G);
  gpio_set_dir(PIN_G, GPIO_IN);
  gpio_pull_up(PIN_G);

  gpio_set_irq_enabled_with_callback(PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &callback);

  gpio_set_irq_enabled(PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {

      if(FLAG_G) {
        printf("fall green \n");
        FLAG_G = 0;
      }    

      if (FLAG_R) {
        printf("fall red \n");
        FLAG_R = 0;
      }
  }
}