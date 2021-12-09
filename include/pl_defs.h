#ifndef PL_DEFS_H
#define PL_DEFS_H
#include <sam.h>

// The syntax for PORT->Group[0] is way too verbose and isn't as clear as PORTA
#define PORTA PORT->Group[0]
#define PORTB PORT->Group[1]
#define PORTC PORT->Group[2]
#define PORTD PORT->Group[3]

// Shorthand for passing the length of a constant array using sizeof
#define ARRAY(arr) arr, (sizeof(arr) / sizeof(arr[0]))

#define ADC_INPUTCTRL_MUXNEG_GND_Val _U_(0x18) /**< \brief (ADC_INPUTCTRL) ADC AIN5 Pin */
#define ADC_INPUTCTRL_MUXNEG_GND     (ADC_INPUTCTRL_MUXNEG_GND_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_SEQCTRL_SEQEN_AIN(n)     (1 << n)

// Fixing EIC constant expression.
#define EIC_EXTINT(value) (1 << value)

// Extern definition of board_id.
extern volatile const uint32_t pl_board_id;

/**
 * Record the board's ID number in flash.
 * This should be done anywhere in a c file in the project, preferably towards the top of main.c
 * This makes the Board Id visible to compute tester (once that's made) and error/startup messages.
 **/
#define PL_BOARD_ID(id) __attribute__((section(".board_id"))) volatile const uint32_t pl_board_id = id;

/**
 * Board ID numbers. Add new IDs as new boards are added to the car.
 * Don't change previous board numbers unless *all* references to it have been removed from *all* programs.
 **/
enum {
  PL_BOARD_DEBUG_ID = 0,
  PL_BOARD_BUTTONBOARD_ID,
  // Insert new boards here
  PL_BOARD_NUM,
};

#endif