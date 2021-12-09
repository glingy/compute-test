#include <samc21.h>
#include <stdbool.h>

#define PORTA9
#define PIN_BTN PORT_PA15
#define PIN_LED PORT_PA15

#define PORTA PORT->Group[0]

static inline bool isBtnPressed() {
  return !(PORTA.IN.reg & PORT_PA28);
}

static inline void setLED(bool on) {
  if(on) {
    PORTA.OUTCLR.reg = PORT_PA15;
  } else {
    PORTA.OUTSET.reg = PORT_PA15;
  }
}

int main() {
  OSCCTRL->OSC48MDIV.reg = OSCCTRL_OSC48MDIV_DIV(0);

  PORTA.DIR.reg    = PORT_PA15;
  PORTA.OUTCLR.reg = PORT_PA15;

  PORTA.PINCFG[28].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;


  while(1) {
    setLED(isBtnPressed());
  }
}