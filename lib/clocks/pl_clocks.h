#ifndef PL_CLOCKS_H
#define PL_CLOCKS_H

#include <sam.h>

static inline void pl_cpu_init() {
  // Running at 48MHz requires setting 1 read-wait-state.
  // Still haven't found a great explanation of this, essentially the flash isn't fast enough
  NVMCTRL->CTRLB.bit.RWS = 1;

  // Remove the clock divider from OSC48M to allow us to run at full speed (48MHz cpu clock)
  OSCCTRL->OSC48MDIV.reg = 0;
  while(OSCCTRL->OSC48MSYNCBUSY.reg) continue;
}

static inline void pl_gclk1_init() {
  // Initialize the clock generator 1 to 8MHz
  // by dividing the internal 48MHz clock
  GCLK->GENCTRL[1].reg
    = GCLK_GENCTRL_SRC_OSC48M
    | GCLK_GENCTRL_DIV(6)
    | GCLK_GENCTRL_GENEN;
}

#endif