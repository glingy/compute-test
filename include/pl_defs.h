#ifndef PL_DEFS_H
#define PL_DEFS_H

// The syntax for PORT->Group[0] is way too verbose and isn't as clear as PORTA
#define PORTA PORT->Group[0]
#define PORTB PORT->Group[1]
#define PORTC PORT->Group[2]
#define PORTD PORT->Group[3]

// Fixing EIC constant expression.
#define EIC_EXTINT(value) (1 << value)

// Shorthand for passing the length of a constant array using sizeof
#define ARRAY(arr) arr, (sizeof(arr) / sizeof(arr[0]))


#endif
