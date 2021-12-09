#ifndef PL_CAN_MESSAGE_H
#define PL_CAN_MESSAGE_H

#include <stdint.h>

/** CAN Standard Filter Types **/
enum {
  // In range of SFID1 <-> SFID2
  CAN_SFT_RANGE = 0x0,
  // One of SFID1 or SFID2 exactly
  CAN_SFT_DUAL,
  // Matches SFID1 with mask of SFID2
  CAN_SFT_CLASSIC,
};

/** CAN Standard Filter Element Configuration **/
enum {
  // Disable filter
  CAN_SFEC_DISABLE = 0x0,
  // Store in Rx FIFO 0 if filter matches
  CAN_SFEC_STF0M,
  // Store in Rx FIFO 1 if filter matches
  CAN_SFEC_STF1M,
  // Reject ID if filter matches
  CAN_SFEC_REJECT,
  // Set priority interrupt flag if filter matches
  CAN_SFEC_PRIORITY,
  // Set priority and store in FIFO 0 if filter matches
  CAN_SFEC_PRIF0M,
  // Set priority and store in FIFO 1 if filter matches
  CAN_SFEC_PRIF1M,
  // Store into Rx Buffer or Debug Message, SFT ignored.
  CAN_SFEC_STRXBUF
};

/** CAN Transmit Frame **/
typedef struct __attribute__((packed)) {
  union {
    struct {
      // Reserved for extended ID
      volatile uint32_t _res1 : 18;
      // 11-bit standard CAN ID
      volatile uint32_t ID    : 11;
      // Is this a Remote Transmission Request?
      volatile uint32_t RTR   : 1;
      // Does this CAN message use an extended ID?
      volatile uint32_t XTD   : 1;
      // Should the ESI bit in CAN Fast Data be transmitted recessive?
      volatile uint32_t ESI   : 1;
    };
    struct {
      // 29-bit extended CAN ID (Ensure is_extended is also set)
      volatile uint32_t EXT_ID  : 29;
      // Is this a Remote Transmission Request?
      volatile uint32_t EXT_RTR : 1;
      // Does this CAN message use an extended ID?
      volatile uint32_t EXT_XTD : 1;
      // Should the ESI bit in CAN Fast Data be transmitted recessive?
      volatile uint32_t EXT_ESI : 1;
    };
    volatile uint32_t T0;
  };

  union {
    struct {
      // Reserved
      volatile uint32_t _reserved3 : 16;
      // Length of the data being sent with this message (up to 8 bytes for standard CAN (64 if CAN FD))
      volatile uint32_t DLC        : 4;
      // If this is CAN FD, should the bit rate be sped up for data?
      volatile uint32_t BRS        : 1;
      // Should this be transmitted using CAN Fast Data?
      volatile uint32_t FDF        : 1;
      // Reserved
      volatile uint32_t _res2      : 1;
      // Should transmit events be stored in the transmit event fifo?
      volatile uint32_t EFC        : 1;
      // Message marker is copied into event FIFO for identification if needed
      volatile uint32_t MM         : 8;
    };
    volatile uint32_t T1;
  };

  union {
    volatile uint8_t bytes[8];
    struct {
      volatile uint32_t DATA0;
      volatile uint32_t DATA1;
    };
  };
} PLCanTxMessage_t;

/** CAN Receive Frame **/
typedef struct __attribute__((packed)) {
  union {
    struct {
      // Reserved for extended ID
      volatile uint32_t _res1 : 18;
      // 11-bit standard CAN ID
      volatile uint32_t ID    : 11;
      // Is this a Remote Transmission Request?
      volatile uint32_t RTR   : 1;
      // Does this CAN message use an extended ID?
      volatile uint32_t XTD   : 1;
      // Should the ESI bit in CAN Fast Data be transmitted recessive?
      volatile uint32_t ESI   : 1;
    };
    struct {
      // 29-bit extended CAN ID (Ensure is_extended is also set)
      volatile uint32_t EXT_ID  : 29;
      // Is this a Remote Transmission Request?
      volatile uint32_t EXT_RTR : 1;
      // Does this CAN message use an extended ID?
      volatile uint32_t EXT_XTD : 1;
      // Should the ESI bit in CAN Fast Data be transmitted recessive?
      volatile uint32_t EXT_ESI : 1;
    };
    volatile uint32_t T0;
  };

  union {
    struct {
      // Receive Timestamp - See Timestamp configuration
      volatile uint32_t RXTS  : 16;
      // Length of the data being sent with this message (up to 8 bytes for standard CAN (64 if CAN FD))
      volatile uint32_t DLC   : 4;
      // If this was CAN FD, the bit rate was sped up for data.
      volatile uint32_t BRS   : 1;
      // This message was sent using CAN Fast Data.
      volatile uint32_t FDF   : 1;
      // Reserved
      volatile uint32_t _res2 : 2;
      // Filter Index which allowed reception of this message
      volatile uint32_t FIDX  : 7;
      // This message was a non-matching frame which was accepted anyway
      volatile uint32_t ANMF  : 1;
    };
    volatile uint32_t T1;
  };

  union {
    volatile uint8_t bytes[8];
    struct {
      volatile uint32_t DATA0;
      volatile uint32_t DATA1;
    };
  };
} PLCanRxMessage_t;

/** CAN Standard Filter Element **/
typedef struct __attribute__((packed)) {
  union {
    // Second filter ID. Can be mask, upper/lower range, or special for rx buffer.
    volatile uint16_t SFID2;
    struct __attribute__((packed)) {
      volatile uint32_t SFID2_BUFIDX : 6;
      volatile uint32_t SFID2_EVENT  : 3;
      volatile uint32_t SFID2_TARGET : 2;
      volatile uint32_t _reserved    : 5;
    };
  };
  // First filter ID. Always is a message id.
  volatile uint32_t SFID1 : 11;
  // Filter configuration. See CAN_SFEC_*
  volatile uint32_t SFEC  : 3;
  // Filter type. See CAN_SFT_*
  volatile uint32_t SFT   : 2;
} PLCanStdFilter_t;

#endif