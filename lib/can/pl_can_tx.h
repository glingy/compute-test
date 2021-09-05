#ifndef PL_CAN_TX_H
#define PL_CAN_TX_H

#include "pl_can_message.h"

#include <pl_defs.h>
#include <sam.h>

// Configure the CAN transmit buffer
static inline void pl_can_tx_config(Can * can,                             // CAN Pointer
                                    volatile PLCanTxMessage_t * tx_buffer, // Tx Buffer pointer
                                    uint32_t num_buffers,                  // Number of dedicated buffers
                                    uint32_t num_fifos,                    // Number of fifo/queue buffers
                                    uint32_t use_queue) {                  // Use a queue instead of a fifo
  // Configure TX buffer
  can->TXBC.reg
    = CAN_TXBC_TBSA((int) tx_buffer)   // Set the address of the buffer
    | (use_queue << CAN_TXBC_TFQM_Pos) // Set whether to use the queue or not
    | CAN_TXBC_NDTB(num_buffers)       // n Dedicated Buffers
    | CAN_TXBC_TBSA(num_fifos);        // n FIFOs/Queue buffers
}


static inline void pl_can_tx_send(Can * can, int tx_buffer_idx) {
  can->TXBAR.reg = (1 << tx_buffer_idx);
}

static inline int pl_can_tx_busy(Can * can, int tx_buffer_idx) {
  return can->TXBRP.reg & (1 << tx_buffer_idx);
}

// ALWAYS check if the fifo is full before putting a message in the fifo
static inline int pl_can_tx_fifo_free(Can * can) {
  return can->TXFQS.bit.TFQF;
}

// The index in the tx buffer array at which to set the next can message to be sent
// for fifos or queues.
static inline int pl_can_tx_fifo_idx(Can * can) {
  return can->TXFQS.bit.TFQPI * 32;
}

#endif