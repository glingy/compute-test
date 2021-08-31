#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#include <stdint.h>

typedef struct __attribute__((packed)) CanTxMessage {
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
} CanTxMessage_t;

#endif