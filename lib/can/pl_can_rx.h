#ifndef PL_CAN_RX_H
#define PL_CAN_RX_H

#include "pl_can_message.h"

#include <pl_defs.h>
#include <sam.h>
#include <stdbool.h>

static inline void pl_can_rx_filter_config(Can * can, volatile PLCanStdFilter_t * filters, int num_filters) {
  // Initialize filter array
  can->SIDFC.reg
    = CAN_SIDFC_LSS(num_filters)      // Number of filters
    | CAN_SIDFC_FLSSA((int) filters); // Starting address of filters
}


#define PL_CAN_RX_FIFO_OVERWRITE true
#define PL_CAN_RX_FIFO_BLOCK     false

static inline void pl_can_rx_fifo0_config(Can * can, volatile PLCanRxMessage_t * buffer, int num_messages, bool overwrite) {
  // Configure FIFO 0 (No watermark)
  can->RXF0C.reg
    = (overwrite ? CAN_RXF0C_F0OM : 0) // Overwrite or Block when full
    | CAN_RXF0C_F0S(num_messages)      // Number of fifo elements
    | CAN_RXF0C_F0SA((int) buffer);    // Starting address of fifo
}

static inline void pl_can_rx_reject_by_default(Can * can) {
  // Reject all frames that don't match filters
  can->GFC.reg
    = CAN_GFC_ANFS_REJECT // REJECT non-matching frames by default.
    | CAN_GFC_ANFE_REJECT // REJECT extended ^
    | CAN_GFC_RRFS        // REJECT remote frames
    | CAN_GFC_RRFE;       // REJECT extended ^
}

// Check if a message is available for processing in fifo 0
static inline uint32_t pl_can_rx_fifo0_has_message(Can * can) {
  return can->RXF0S.bit.F0FL;
}

// Get the most recent message index from the receive fifo 0
static inline uint32_t pl_can_rx_fifo0_get(Can * can) {
  return can->RXF0S.bit.F0GI;
}

// Acknowledge the most recent CAN message in the receive FIFO 0
// Call *after* you have processed the message.
static inline void pl_can_rx_fifo0_ack(Can * can, int idx) {
  can->RXF0A.reg = idx;
}

#endif