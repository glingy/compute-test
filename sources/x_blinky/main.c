#include <samc21.h>

#define PORTA PORT->Group[0]

int main() {
  PORTA.DIR.reg    = PORT_PA12 | PORT_PA13 | PORT_PA14 | PORT_PA15;
  PORTA.OUTSET.reg = PORT_PA12 | PORT_PA13 | PORT_PA15;
  PORTA.OUTSET.reg = PORT_PA14;

  while(1) {
    for(int i = 0; i < 0x40000; i++) {
      __NOP();
    }
    PORTA.OUTTGL.reg = PORT_PA12;
    for(int i = 0; i < 0x40000; i++) {
      __NOP();
    }
    PORTA.OUTTGL.reg = PORT_PA12 | PORT_PA15;
  }
}