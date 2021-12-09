#include <math.h>
#include <pl_can.h>
#include <pl_clocks.h>
#include <samc21.h>
#include <stdbool.h>
#include <stdlib.h>

// If possible, please use constants for any CAN messages you send or receive.
// This helps change them if needed so we don't have to search through code.

/** CAN MESSAGES **/
#define ID_BTN 0x101

/** CAN Transmit Buffer **/
volatile __ALIGNED(4) PLCanTxMessage_t can0_tx_buffer[1] = {
  {
    .ID    = ID_BTN,
    .DLC   = 8,
    .bytes = { 0, 1, 2, 3, 4, 5, 6, 7 },
  },
};

/** CAN Receive Buffer **/
volatile __ALIGNED(4) PLCanRxMessage_t can0_rx_buffer[8];

/** CAN Receive Filters **/
volatile __ALIGNED(4) PLCanStdFilter_t can0_filters[] = {
  {
    // Filter exactly 0x101 (Mask with 0xFFFF) into FIFO 0.
    .SFT   = CAN_SFT_CLASSIC,
    .SFEC  = CAN_SFEC_STF0M,
    .SFID1 = 0x101,
    .SFID2 = 0xFFFF,
  }
};


int main() {

  /** INITIALIZATION **/
  pl_cpu_init();

  // Enable the GCLK1 for the CAN clock to reference
  pl_gclk1_init();

  // Initialize CAN
  pl_can_init(CAN0);
  pl_can_tx_config(CAN0, can0_tx_buffer, 1, 0, false);

  //pl_can_rx_reject_by_default(CAN0);
  //pl_can_rx_filter_config(CAN0, ARRAY(can0_filters));
  //pl_can_rx_fifo0_config(CAN0, ARRAY(can0_rx_buffer), false);

  pl_can_start(CAN0);

  // Initialize GPIO
  PORTA.DIRSET.reg     = PORT_PA15;
  PORTA.DIRCLR.reg     = PORT_PA28;
  PORTA.OUTCLR.reg     = PORT_PA15;
  PORTA.OUTSET.reg     = PORT_PA28;
  PORTA.PINCFG[28].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;

  /** RUN **/
  bool button = false;
  while(1) {
    if(pl_can_rx_fifo0_has_message(CAN0)) {
      int msg_id = pl_can_rx_fifo0_get(CAN0);
      //volatile PLCanRxMessage_t * msg = can0_rx_buffer + msg_id;

      // Do processing on message data...

      pl_can_rx_fifo0_ack(CAN0, msg_id);
      PORTA.OUTTGL.reg = PORT_PA15;
    }


    if(!(PORTA.IN.reg & PORT_PA28) && !button) {
      button = true;
      if(!pl_can_tx_busy(CAN0, 0)) {
        PORTA.OUTTGL.reg = PORT_PA15;
        pl_can_tx_send(CAN0, 0);
      }
    } else if((PORTA.IN.reg & PORT_PA28) && button) {
      button = false;
    }
  }
}