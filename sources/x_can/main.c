#include <math.h>
#include <pl_can.h>
#include <pl_clocks.h>
#include <samc21.h>
#include <stdlib.h>


volatile __ALIGNED(4) PLCanTxMessage_t can0_tx_buffer[1];
volatile __ALIGNED(4) PLCanRxMessage_t can0_rx_buffer[1];

int main() {
  pl_cpu_init();

  // Enable the GCLK1 for the CAN clock to reference
  pl_gclk1_init();

  pl_can_init(CAN0);
  pl_can_tx_config(CAN0, can0_tx_buffer, 1, 0, 0);
  pl_can_start(CAN0);

  // volatile double a = cos(90.0);
  // can0_tx_buffer = malloc(128);

  can0_tx_buffer[0].ID    = 0x102;
  can0_tx_buffer[0].DLC   = 8;
  can0_tx_buffer[0].DATA0 = 0xEFBEADDE;
  can0_tx_buffer[0].DATA1 = 0xADDEEFBE;

  pl_can_tx_send(CAN0, 0);

  PORTA.DIR.reg = PORT_PA15;

  while(1) {
    for(int i = 0; i < 0x80000; i++) {
      __NOP();
    }
    PORTA.OUTTGL.reg = PORT_PA15;
  }
}