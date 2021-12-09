#ifndef PL_CAN_H
#define PL_CAN_H

#include "pl_can_rx.h"
#include "pl_can_tx.h"
#include "pl_can_types.h"

#include <pl_defs.h>
#include <sam.h>

/**
 * Default can messages.
 * These should be present in all programs to send an error message (if needed) and the startup message.
 * The startup message should be sent once initialization is complete (or as complete as possible before CAN is disabled).
 * User can messages should start at index 2.
 **/
enum {
  PL_CAN_TX_ERROR_MSG = 0,
  PL_CAN_TX_STARTUP_MSG,
};

#define PL_CAN_TX_ERROR_BUFFER \
  {                            \
    .ID    = 0x1,              \
    .DLC   = 0x4,              \
    .bytes = { 0 },            \
  }

#define PL_CAN_TX_STARTUP_BUFFER \
  {                              \
    .ID    = 0x51,               \
    .DLC   = 0x4,                \
    .bytes = { 0 },              \
  }

static inline void pl_can_clock_init(Can * can) {
  // Enable the CAN clock using GLCK1
  GCLK->PCHCTRL[can == CAN0 ? CAN0_GCLK_ID : CAN1_GCLK_ID].reg
    = GCLK_PCHCTRL_GEN_GCLK1
    | GCLK_PCHCTRL_CHEN;
}

static inline void pl_can_begin_config(Can * can) {
  // Enable the AHB Clock (Must be done before ANY can register accesses)
  if(can == CAN0)
    MCLK->AHBMASK.bit.CAN0_ = 1;
  else
    MCLK->AHBMASK.bit.CAN1_ = 1;

  // Allow changing configuration registers while still in initialization mode
  can->CCCR.bit.CCE = 1;
}

static inline void pl_can_baud_config(Can * can) {
  // Configure Bit Rate (125k, 4bit SJW, 11 bit Pre-sample, 4 bit post-sample)
  // These registers are read as one more than programmed
  can->NBTP.reg
    = CAN_NBTP_NBRP(3)    // Prescaler of 4 (4 clocks = 1TQ)
    | CAN_NBTP_NSJW(3)    // SJW of 4 (See reference document)
    | CAN_NBTP_NTSEG1(10) // Pre-sample of 11
    | CAN_NBTP_NTSEG2(3); // Post-sample of 4
}

static inline void pl_can_start(Can * can) {

  // Clear CCE and INIT to begin initialization
  // And enable Transmit Pause (wait 2 idles between sending to let other messages through)
  can->CCCR.reg = 0 | CAN_CCCR_TXP;

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

static inline void pl_can_init(Can * can) {
  pl_can_clock_init(can);
  pl_can_begin_config(can);
  pl_can_baud_config(can);
}

#endif
