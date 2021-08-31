#ifndef PRISUM_CAN_IMPL_H
#define PRISUM_CAN_IMPL_H

#include <defs.h>
#include <message.h>
#include <sam.h>

static inline void can_clock_init(Can * can) {
  // Enable the CAN clock using GLCK1
  GCLK->PCHCTRL[can == CAN0 ? CAN0_GCLK_ID : CAN1_GCLK_ID].reg
    = GCLK_PCHCTRL_GEN_GCLK1
    | GCLK_PCHCTRL_CHEN;
}

static inline void can_begin_config(Can * can) {
  if(can == CAN0)
    MCLK->AHBMASK.bit.CAN0_ = 1;
  else
    MCLK->AHBMASK.bit.CAN1_ = 1;

  // Allow changing configuration registers while still in initialization mode
  can->CCCR.bit.CCE = 1;
}

static inline void can_baud_config(Can * can) {
  // Configure Bit Rate (125k, 4bit SJW, 11 bit Pre-sample, 4 bit post-sample)
  // These registers are read as one more than programmed
  can->NBTP.reg
    = CAN_NBTP_NBRP(3)    // Prescaler of 4 (4 clocks = 1TQ)
    | CAN_NBTP_NSJW(3)    // SJW of 4 (See reference document)
    | CAN_NBTP_NTSEG1(10) // Pre-sample of 11
    | CAN_NBTP_NTSEG2(3); // Post-sample of 4
}

static inline void can_tx_config(Can * can,
                                 volatile CanTxMessage_t * tx_buffer,
                                 uint32_t num_buffers,
                                 uint32_t num_fifos,
                                 uint32_t use_queue) {
  // Configure TX buffer
  can->TXBC.reg
    = CAN_TXBC_TBSA((int) tx_buffer)   // Set the address of the buffer
    | (use_queue << CAN_TXBC_TFQM_Pos) // Set whether to use the queue or not
    | CAN_TXBC_NDTB(num_buffers)       // n Dedicated Buffers
    | CAN_TXBC_TBSA(num_fifos);        // n FIFOs/Queue buffers
}

static inline void can_start(Can * can) {

  // Clear CCE and INIT to begin initialization
  can->CCCR.reg = 0;

  if(can == CAN0) {
    // Configure pin mux to CAN0
    PORTA.PMUX[12].reg
      = PORT_PMUX_PMUXE(MUX_PA24G_CAN0_TX)
      | PORT_PMUX_PMUXO(MUX_PA25G_CAN0_RX);

    // Enable pin mux
    PORTA.PINCFG[24].reg = PORT_PINCFG_PMUXEN;
    PORTA.PINCFG[25].reg = PORT_PINCFG_PMUXEN;
  } else {
    // TODO: Fix pinout for CAN1
    // Enable pins
    PORTA.PMUX[12].reg
      = PORT_PMUX_PMUXE(MUX_PA24G_CAN0_TX)
      | PORT_PMUX_PMUXO(MUX_PA25G_CAN0_RX);

    PORTA.PINCFG[24].reg = PORT_PINCFG_PMUXEN;
    PORTA.PINCFG[25].reg = PORT_PINCFG_PMUXEN;
  }

  while(can->CCCR.bit.INIT) continue;
}

static inline void can_init(Can * can) {
  can_clock_init(can);
  can_begin_config(can);
  can_baud_config(can);
}

#endif