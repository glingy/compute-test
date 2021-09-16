

## CAN:
 - Baud Rate 125k
N GCLK_CAN periods = 1 Time Quanta
N Time Quanta = Bit
Read reference for CAN timing for more details
#### Current Configuration:
 - 1TQ = 500ns = 8MHz reference / 4 (16TQ = 125k Baud Rate)
 - DBTP is used for CAN FD (Flexible Data-Rate which we're not using)
 - Use NBTP for configuting data rate
  - Synchronization Jump Width: 4TQ
  - Prescaler: 1TQ = 4 CLK periods
  - Time segment before sample point (Propagation Delay): 11TQ
  - Time segment after sample point: 4TQ
  - 1TQ (sync always 1TQ) -> Bit set -> 11TQ Prop. Delay -> Bit Read -> 4TQ Time after sample point (16TQ per bit)
  - SJW -> 2% OSC48M tolerance @ 125k should be 4 according to formula in reference document on page 7.

## Clocks:

GLCK_GEN0 -> 48MHz -> 48MHz internal oscillator with no division.
 - CPU
GCLK_GEN1 -> 8MHz  -> 48MHz internal oscillator with 6 division.
 - CAN

## Compilation Notes:
 - flto causes everything to crash spectacularly...
 
