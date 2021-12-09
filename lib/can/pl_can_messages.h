#ifndef PL_CAN_MESSAGES_H
#define PL_CAN_MESSAGES_H

/**
 * This file contains the current messages available in the car.
 * All message IDs in use should be listed here along with their data definition.
 **/

enum {
  PL_CAN_MSG_ERROR_ID  = 0x1,
  PL_CAN_MSG_BUTTON_ID = 0x101,
};

typedef struct {

} PLMsgButton_t;

#endif